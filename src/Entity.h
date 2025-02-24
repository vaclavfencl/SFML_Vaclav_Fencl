#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
public:
    Entity();
    virtual void update(float deltaTime);
    virtual void render(sf::RenderWindow& window);
    virtual void handleInput();
};

#endif
