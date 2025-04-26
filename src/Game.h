#pragma once
#include <SFML/Graphics.hpp>
#include "entities/Ball.h"
#include "entities/Paddle.h"

class Game {
public:
    Game(sf::RenderWindow& window); 

    void update();
    void render();

private:
    sf::RenderWindow& window; 

    int screenWidth = 800;
    int screenHeight = 600;
    int score1 = 0;
    int score2 = 0;
    sf::Font font;
    sf::Text scoreText1;
    sf::Text scoreText2;
    sf::Clock clock;
    Ball ball;
    Paddle paddle;
    Paddle paddleAi;
};
