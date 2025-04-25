#pragma once
#include "Ball.h"

class Paddle {
public:
    float screenHeight;
    Paddle(float x, float y, float screenHeight);

    void updatePlayer(float dt);               
    void updateAI(float dt, const Ball& ball);

    void render(sf::RenderWindow& window);

    void moveUp(float dt);
    void moveDown(float dt);

    sf::FloatRect getBounds() const;
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;


private:
    sf::RectangleShape shape;
    float speed = 300.f;
};
