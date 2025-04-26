#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
public:
    Entity();
    virtual ~Entity() = default;

    virtual void update(float deltaTime) = 0;
    virtual void handleInput() {}

    virtual void render(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    void setPosition(float x, float y);

protected:
    sf::Shape* shape = nullptr;  
};

#endif
