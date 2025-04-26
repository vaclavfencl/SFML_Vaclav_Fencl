#pragma once
#ifndef BALL_H
#define BALL_H

#include "../Entity.h"

class Ball : public Entity {
public:
    Ball();
    void update(float deltaTime) override;
    void handleInput() override {}
    void bounceX();
    void bounceY();
    void reset();
    void setDirection(float offsetY);
    sf::Vector2f getDirection() const;
    void setVelocity(sf::Vector2f dir);

    int bounced = 2;
    float radius = 20.f;

private:
    sf::CircleShape circleShape;
    sf::Vector2f direction;
    float speed = 400.f;

    void launch();
};

#endif
