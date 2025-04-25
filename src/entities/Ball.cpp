#include "Ball.h"
#include <cmath>
#include <cstdlib>

Ball::Ball() {
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(390.f, 290.f);
    launch();
}

void Ball::launch() {
    direction = sf::Vector2f(0.f, 0.f);

    while (true) {
        float angle = static_cast<float>(std::rand() % 360);  
        
            if ((static_cast<int>(angle) >= 30 and static_cast<int>(angle) <= 60) or (static_cast<int>(angle) >= 210 and static_cast<int>(angle) <= 240))
            {
                float rad = angle * 3.14159f / 180.f;
                direction.x = std::cos(rad);
                direction.y = std::sin(rad);
                break; 
            }
    }
}

void Ball::update(float deltaTime) {
    int steps = 4;
    float step = deltaTime / steps;

    for (int i = 0; i < steps; ++i) {
        shape.move(direction * speed * step);
    }
}

void Ball::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

void Ball::bounceX() {
    direction.x *= -1.f;
}

void Ball::bounceY() {
    direction.y *= -1.f;
}

void Ball::reset() {
    shape.setPosition(390.f, 290.f);
    bounced = 2;
    launch();
}

void Ball::setDirection(float offsetY) {
    if (offsetY < -1.f) offsetY = -1.f;
    if (offsetY > 1.f) offsetY = 1.f;

    float signX = (direction.x < 0) ? -1.f : 1.f;

    direction = sf::Vector2f(signX, offsetY);
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0.f)
        direction /= length; 
}


sf::Vector2f Ball::getDirection() const {
    return direction;
}

void Ball::setVelocity(sf::Vector2f dir) {
    direction = dir;
}

void Ball::render(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::Vector2f Ball::getPosition() const{
    return shape.getPosition();
}

sf::FloatRect Ball::getBounds() const {
    return shape.getGlobalBounds();
}
