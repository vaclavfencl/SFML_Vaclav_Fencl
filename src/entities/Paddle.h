#pragma once
#ifndef PADDLE_H
#define PADDLE_H

#include "Ball.h"
#include "../Entity.h"
#include "../core/TextureManager.h"

class Paddle : public Entity {
public:
    Paddle(float x, float y, float screenHeight);

    void updatePlayer(float dt);
    void updateAI(float dt, const Ball& ball);
    void update(float dt) override {} 
    void handleInput() override {}
    void render(sf::RenderWindow& window);
    void setTexture(sf::Texture& texture);

    sf::Vector2f getSize() const;

private:
    sf::RectangleShape rectShape;
    float screenHeight;
    float speed = 300.f;

    void moveUp(float dt);
    void moveDown(float dt);
};

#endif
