#pragma once
#ifndef GAME_H
#define GAME_H

#include "entities/Ball.h"
#include "entities/Paddle.h"
#include "core/TextureManager.h"
#include <SFML/Graphics.hpp>

class Game {
public:
    Game(sf::RenderWindow& window);

    void update(float dt);
    void render();

private:
    sf::RenderWindow& window;
    int screenWidth = 800;
    int screenHeight = 600;
    sf::Font font;
    int score1 = 0;
    int score2 = 0;
    sf::Text scoreText1;
    sf::Text scoreText2;

    Ball ball;
    Paddle paddle;
    Paddle paddleAi;
};

#endif