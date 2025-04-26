#include "Entity.h"

Entity::Entity() {}

void Entity::render(sf::RenderWindow& window) {
    if (shape)
        window.draw(*shape);
}

sf::Vector2f Entity::getPosition() const {
    if (shape)
        return shape->getPosition();
    return sf::Vector2f();
}

sf::FloatRect Entity::getBounds() const {
    if (shape)
        return shape->getGlobalBounds();
    return sf::FloatRect();
}

void Entity::setPosition(float x, float y) {
    if (shape)
        shape->setPosition(x, y);
}
