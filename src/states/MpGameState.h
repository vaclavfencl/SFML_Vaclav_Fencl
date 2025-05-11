#pragma once
#include "../core/IGameState.h"
#include "../core/StateHandler.h"
#include "../entities/Ball.h"
#include "../entities/Paddle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <thread>
#include <atomic>

class MpGameState : public IGameState {
public:
    MpGameState(StateHandler& handler, sf::RenderWindow& window, bool isHost);
    ~MpGameState();

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    StateHandler& stateHandler;
    sf::RenderWindow& window;
    bool isHost;
    std::atomic<bool> running;
    std::atomic<bool> isConnected;

    sf::TcpSocket socket;
    sf::TcpListener listener;
    std::thread networkThread;

    Ball ball;
    Paddle paddleHost;
    Paddle paddleClient;

    sf::Font font;
    sf::Text scoreText1, scoreText2;

    int score1 = 0;
    int score2 = 0;

    void hostListen();
    void clientConnect();
    void networkLoop();
    void sendCommand(const std::string& command);
};
