#include "Ball.h"
#include <cmath>
#include <cstdlib>

Ball::Ball() {
    circleShape.setRadius(radius);
    circleShape.setFillColor(sf::Color::Red);
    circleShape.setPosition(390.f, 290.f);
    shape = &circleShape;  
    launch();
}

void Ball::launch() {
    direction = sf::Vector2f(0.f, 0.f);

    while (true) {
        float angle = static_cast<float>(std::rand() % 360);

        if ((static_cast<int>(angle) >= 30 && static_cast<int>(angle) <= 60) ||
            (static_cast<int>(angle) >= 210 && static_cast<int>(angle) <= 240)) {
            float rad = angle * 3.14159f / 180.f;
            direction.x = std::cos(rad);
            direction.y = std::sin(rad);
            break;
        }
    }
}

void Ball::setTexture(sf::Texture& texture) {
    sprite.setTexture(texture); 
    animation = AnimationManager(sprite, 4, 0.15f, sf::Vector2i(20, 20)); 
    //sprite.setOrigin(10.f, 10.f);
    sprite.setScale(2.f, 2.f);
}


void Ball::update(float deltaTime) {
    int steps = 4;
    float step = deltaTime / steps;

    for (int i = 0; i < steps; ++i) {
        shape->move(direction * speed * step);
    }
    sprite.setPosition(shape->getPosition());

    animation.update(deltaTime);
}

void Ball::bounceX() {
    direction.x *= -1.f;
}

void Ball::bounceY() {
    direction.y *= -1.f;
}

void Ball::reset() {
    setPosition(390.f, 290.f);
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
    window.draw(sprite);
    //window.draw(circleShape);
}

void Ball::setPosition(float x, float y) {
    if (shape)
        shape->setPosition(x, y);
    sprite.setPosition(x, y); 
}
