#pragma once
#ifndef APPLE_H
#define APPLE_H

#include <SFML/Graphics.hpp>
#include "../Entity.h"

class Apple : public Entity {
public:
    Apple();
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::CircleShape shape;
};

#endif
