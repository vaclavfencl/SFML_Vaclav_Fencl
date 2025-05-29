#include "MpGameState.h"
#include "MenuState.h"
#include "../core/SoundManager.h"
#include "../core/TextureManager.h"
#include <iostream>
#include <thread>

MpGameState::MpGameState(StateHandler& handler, sf::RenderWindow& win, bool host)
    : stateHandler(handler), window(win), isHost(host),
    paddleHost(30.f, 50.f, 600), paddleClient(750.f, 50.f, 600),
    running(true), isConnected(false)
{
    font.loadFromFile("Thirdparty/fonts/Roboto-Light.ttf");

    auto& paddleTex = TextureManager::getTexture("Thirdparty/textures/paddle.png");
    auto& ballTex = TextureManager::getTexture("Thirdparty/textures/ball.png");

    SoundManager::loadSound("pong", "Thirdparty/sounds/pong.wav");
    SoundManager::loadSound("score", "Thirdparty/sounds/score.wav");

    paddleHost.setTexture(paddleTex);
    paddleClient.setTexture(paddleTex);
    ball.setTexture(ballTex);

    scoreText1.setFont(font);
    scoreText1.setCharacterSize(30);
    scoreText1.setFillColor(sf::Color::White);
    scoreText1.setPosition(200.f, 20.f);

    scoreText2.setFont(font);
    scoreText2.setCharacterSize(30);
    scoreText2.setFillColor(sf::Color::White);
    scoreText2.setPosition(550.f, 20.f);

    if (!isHost)
        std::swap(paddleHost, paddleClient);

    if (isHost)
        networkThread = std::thread(&MpGameState::hostListen, this);
    else
        networkThread = std::thread(&MpGameState::clientConnect, this);
}

MpGameState::~MpGameState() {
    running = false;
    if (networkThread.joinable()) networkThread.join();
    socket.disconnect();
}

void MpGameState::hostListen() {
    if (listener.listen(4500) != sf::Socket::Done) {
        std::cerr << "[HOST] Failed to listen on port 4500\n";
        return;
    }

    std::thread([this]() {
        sf::UdpSocket udpSocket;
        udpSocket.setBlocking(false);
        sf::Packet packet;
        packet << std::string("PONG_HOST");

        while (running && !isConnected) {
            udpSocket.send(packet, sf::IpAddress::Broadcast, 4502);
            sf::sleep(sf::seconds(1));
        }
        }).detach();

        std::cout << "[HOST] Listening on LAN IP: " << sf::IpAddress::getLocalAddress() << ":4500\n";

        if (listener.accept(socket) == sf::Socket::Done) {
            socket.setBlocking(false);
            std::cout << "[HOST] Client connected\n";
            isConnected = true;
            std::thread(&MpGameState::networkLoop, this).detach();
        }
}


void MpGameState::clientConnect() {
    sf::UdpSocket udpSocket;
    if (udpSocket.bind(4502) != sf::Socket::Done) {
        std::cerr << "[CLIENT] Failed to bind UDP socket\n";
        return;
    }

    udpSocket.setBlocking(false);
    sf::IpAddress hostIp;
    sf::Clock timeoutClock;
    bool foundHost = false;

    while (timeoutClock.getElapsedTime().asSeconds() < 5.0f) {
        sf::Packet packet;
        sf::IpAddress sender;
        unsigned short port;

        if (udpSocket.receive(packet, sender, port) == sf::Socket::Done) {
            std::string header;
            if (packet >> header && header == "PONG_HOST") {
                hostIp = sender;
                foundHost = true;
                break;
            }
        }
        sf::sleep(sf::milliseconds(100));
    }

    udpSocket.unbind();

    if (!foundHost) {
        std::cerr << "[CLIENT] Could not find host on LAN\n";
        return;
    }

    std::cout << "[CLIENT] Found host at " << hostIp.toString() << ", attempting to connect...\n";

    if (socket.connect(hostIp, 4500, sf::seconds(5)) == sf::Socket::Done) {
        socket.setBlocking(false);
        std::cout << "[CLIENT] Connected to host\n";
        isConnected = true;
        std::thread(&MpGameState::networkLoop, this).detach();
    }
    else {
        std::cerr << "[CLIENT] Connection to host failed\n";
    }
}


void MpGameState::networkLoop() {
    sf::Clock rateLimiter;
    const sf::Time targetFrameTime = sf::seconds(1.f / 60.f);  

    while (running) {
        if (!isConnected) {
            sf::sleep(targetFrameTime);
            continue;
        }

        sf::Time elapsed = rateLimiter.getElapsedTime();
        if (elapsed < targetFrameTime) {
            sf::sleep(targetFrameTime - elapsed);
        }
        rateLimiter.restart();

        if (isHost) {
            sf::Packet inputPacket;
            if (socket.receive(inputPacket) == sf::Socket::Done) {
                float y;
                if (inputPacket >> y) {
                    paddleClient.setPosition(paddleClient.getPosition().x, y);
                }
            }

            sf::Packet gamePacket;
            gamePacket.clear();
            gamePacket << ball.getPosition().x << ball.getPosition().y
                << ball.getDirection().x << ball.getDirection().y
                << paddleHost.getPosition().x << paddleHost.getPosition().y
                << score1 << score2;
            if (socket.send(gamePacket) != sf::Socket::Done) {
                std::cerr << "[HOST] Failed to send packet!\n";
            }
        }
        else {
            sf::Packet inputPacket;
            inputPacket << paddleClient.getPosition().y;
            if (socket.send(inputPacket) != sf::Socket::Done) {
                std::cerr << "[CLIENT] Failed to send input!\n";
            }

            sf::Packet gamePacket;
            if (socket.receive(gamePacket) == sf::Socket::Done) {
                std::lock_guard<std::mutex> lock(packetMutex);
                latestPacket = gamePacket;
                hasNewPacket = true;
                float bx, by, dx, dy, hostX, hostY;
                int s1, s2;
                if (gamePacket >> bx >> by >> dx >> dy >> hostX >> hostY >> s1 >> s2) {
                    ball.setPosition(bx, by);
                    ball.setVelocity({ dx, dy });
                    paddleHost.setPosition(hostX, hostY);
                    score1 = s1;
                    score2 = s2;
                }
                else {
                    std::cerr << "[CLIENT] Failed to parse packet!\n";
                }
            }
        }
    }
}


void MpGameState::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            if (isHost) sendCommand("EXIT"); 
            running = false;
            stateHandler.changeState(std::make_shared<MenuState>(stateHandler, window));
        }
    }
}

void MpGameState::update(float dt) {
    if (!isConnected) return;

    if (isHost) {
        paddleHost.updatePlayer(dt);
        ball.update(dt);

        if (ball.getPosition().y < 0.f || ball.getPosition().y + 40.f > 600.f){
            ball.bounceY();
            SoundManager::playSound("pong");
            sendCommand("SOUND:pong");
        }

        if (ball.getBounds().intersects(paddleHost.getBounds())) {
            if (ball.getDirection().x < 0 && ball.bounced != 1) {
                ball.setPosition(paddleHost.getPosition().x + paddleHost.getSize().x + 0.1f, ball.getPosition().y);
                float centerDiff = ball.getPosition().y + ball.radius - (paddleHost.getPosition().y + paddleHost.getSize().y / 2.f);
                ball.setDirection(centerDiff / (paddleHost.getSize().y / 2.f));
                ball.bounceX();
                ball.bounced = 1;
                SoundManager::playSound("pong");
                sendCommand("SOUND:pong");
            }
        }

        if (ball.getBounds().intersects(paddleClient.getBounds())) {
            if (ball.getDirection().x > 0 && ball.bounced != 0) {
                ball.setPosition(paddleClient.getPosition().x - ball.radius * 2.f - 0.1f, ball.getPosition().y);
                float centerDiff = ball.getPosition().y + ball.radius - (paddleClient.getPosition().y + paddleClient.getSize().y / 2.f);
                ball.setDirection(centerDiff / (paddleClient.getSize().y / 2.f));
                ball.bounceX();
                ball.bounced = 0;
                SoundManager::playSound("pong");
                sendCommand("SOUND:pong");
            }
        }

        if (ball.getPosition().x <= 0.f) {
            score2++;
            SoundManager::playSound("score");
            sendCommand("SOUND:score");
            ball.reset();
        }

        if (ball.getPosition().x + ball.radius * 2 >= 800) {
            score1++;
            SoundManager::playSound("score");
            sendCommand("SOUND:score");
            ball.reset();
        }
    }
    else {
        paddleClient.updatePlayer(dt);

        std::lock_guard<std::mutex> lock(packetMutex);
        if (hasNewPacket) {
            float bx, by, dx, dy, hostX, hostY;
            int s1, s2;
            if (latestPacket >> bx >> by >> dx >> dy >> hostX >> hostY >> s1 >> s2) {
                ball.setPosition(bx, by);
                ball.setVelocity({ dx, dy });
                paddleHost.setPosition(hostX, hostY);
                score1 = s1;
                score2 = s2;
            }
            hasNewPacket = false;
        }
    }

    scoreText1.setString(std::to_string(score1));
    scoreText2.setString(std::to_string(score2));
}

void MpGameState::render(sf::RenderWindow& window) {
    window.clear();
    paddleHost.render(window);
    paddleClient.render(window);
    ball.render(window);
    window.draw(scoreText1);
    window.draw(scoreText2);
}

void MpGameState::sendCommand(const std::string& command) {
    sf::Packet packet;
    packet << std::string("COMMAND") << command;
    socket.send(packet);
}

