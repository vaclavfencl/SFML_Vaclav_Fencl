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
    int screenWidth = 800;
    int screenHeight = 600;
    sf::Font font; //add font, add score.
    int score1=0;
    int score2=0;
    sf::Text scoreText1;
    sf::Text scoreText2;
    


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
