#pragma once
#ifndef Ball_H
#define Ball_H

#include "../Entity.h"

class Ball : public Entity {
public:
    Ball();
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    int bounced = 2;
    float radius = 20.f;
    void setPosition(float x, float y);

    void bounceX();
    void bounceY();
    void reset();

    void setDirection(float offsetY);
    sf::Vector2f getDirection() const;
    void setVelocity(sf::Vector2f dir);

private:
    sf::CircleShape shape;
    sf::Vector2f direction;
    float speed = 400.f;

    void launch();
};

#endif
