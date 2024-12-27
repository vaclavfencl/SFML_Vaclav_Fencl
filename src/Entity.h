#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
public:
    Entity();
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    void handleInput();

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;  
    float speed;
};

#endif
