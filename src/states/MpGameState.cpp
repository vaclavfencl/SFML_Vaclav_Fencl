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
    if (listener.accept(socket) == sf::Socket::Done) {
        socket.setBlocking(false);
        std::cout << "[HOST] Client connected\n";
        isConnected = true;
        std::thread(&MpGameState::networkLoop, this).detach();
    }
}

void MpGameState::clientConnect() {
    if (socket.connect("127.0.0.1", 4500, sf::seconds(5)) == sf::Socket::Done) {
        socket.setBlocking(false);
        std::cout << "[CLIENT] Connected to host\n";
        isConnected = true;
        std::thread(&MpGameState::networkLoop, this).detach();
    }
    else {
        std::cerr << "[CLIENT] Connection failed\n";
    }
}

void MpGameState::networkLoop() {
    while (running) {
        if (!isConnected) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }


        /*sf::Packet packet;
        if (socket.receive(packet) == sf::Socket::Done) {
            std::string type, data;
            if (packet >> type >> data && type == "COMMAND") {
                std::cout << "[COMMAND RECEIVED] " << data << "\n";

                if (data.rfind("SOUND:", 0) == 0) {
                    std::string soundName = data.substr(6);
                    SoundManager::playSound(soundName);
                }
                else if (data == "EXIT") {
                    std::cout << "[COMMAND] Exit requested\n";
                    running = false;
                    stateHandler.changeState(std::make_shared<MenuState>(stateHandler, window));
                }
                else {
                    std::cerr << "[COMMAND] Unknown command: " << data << "\n";
                }
            }
        }*/

        if (isHost) {
            sf::Packet inputPacket;
            if (socket.receive(inputPacket) == sf::Socket::Done) {
                float y;
                if (inputPacket >> y) {
                    paddleClient.setPosition(paddleClient.getPosition().x, y);
                    std::cout << "[HOST] Received client paddle Y: " << y << "\n";
                }
            }

            sf::Packet gamePacket;
            gamePacket << ball.getPosition().x << ball.getPosition().y
                << ball.getDirection().x << ball.getDirection().y
                << paddleHost.getPosition().y //<< paddleClient.getPosition().y
                << score1 << score2;
            socket.send(gamePacket);
        }
        else {
            sf::Packet inputPacket;
            inputPacket << paddleClient.getPosition().y;
            socket.send(inputPacket);
            std::cout << "[CLIENT] Sent paddle Y: " << paddleClient.getPosition().y << "\n";

            sf::Packet gamePacket;
            if (socket.receive(gamePacket) == sf::Socket::Done) {
                float bx, by, dx, dy, hostY, clientY;
                int s1, s2;
                if (gamePacket >> bx >> by >> dx >> dy >> hostY >> /*clientY >>*/ s1 >> s2) {
                    ball.setPosition(bx, by);
                    ball.setVelocity(sf::Vector2f(dx, dy));
                    paddleHost.setPosition(paddleHost.getPosition().x, hostY);
                    //paddleClient.setPosition(paddleClient.getPosition().x, clientY);
                    score1 = s1;
                    score2 = s2;
                    std::cout << "[CLIENT] Game updated: Ball(" << bx << ", " << by << "), Scores(" << s1 << ":" << s2 << ")\n";
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(8));
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
        //ball.update(dt);
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

