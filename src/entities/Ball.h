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

    void bounceX();
    void bounceY();
    void reset();

private:
    sf::CircleShape shape;
    sf::Vector2f direction;
    float speed = 400.f;

    void launch();
};

#endif
