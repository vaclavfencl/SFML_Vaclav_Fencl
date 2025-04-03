#include "Ball.h"
#include <cmath>
#include <cstdlib>

Ball::Ball() {
    shape.setRadius(20.0f);
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
    shape.move(direction * speed * deltaTime);
}

void Ball::bounceX() {
    direction.x *= -1.f;
}

void Ball::bounceY() {
    direction.y *= -1.f;
}

void Ball::reset() {
    shape.setPosition(390.f, 290.f);
    launch();
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
