#include "Entity.h"

Entity::Entity() : speed(200.f), velocity(0.f, 0.f) {
    shape.setRadius(20.0f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(400.f, 300.f);
}

void Entity::handleInput() {
    velocity.x = 0.f;
    velocity.y = 0.f;

    // Check WASD input for movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        velocity.y = -1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        velocity.y = 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocity.x = -1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocity.x = 1.f;
    }

    // Normalize diagonal movement (optional)
    if (velocity.x != 0.f && velocity.y != 0.f) {
        velocity.x *= 0.7071f;  // 1 / sqrt(2)
        velocity.y *= 0.7071f;
    }
}

void Entity::update(float deltaTime) {
    handleInput();  
    shape.move(velocity * speed * deltaTime);
}

void Entity::render(sf::RenderWindow& window) {
    window.draw(shape);
}
