#pragma once
#ifndef GAME_H
#define GAME_H

#include "entities/Ball.h"
#include "entities/Paddle.h"

class Game {
public:
    Game();
    void run();

private:
    sf::Clock clock;
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    Ball ball;
    Paddle paddle;
    Paddle paddleAi;
};

#endif
