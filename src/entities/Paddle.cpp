#include "Paddle.h"

Paddle::Paddle(float x, float y) {
    shape.setSize(sf::Vector2f(20.f, 100.f));
    shape.setFillColor(sf::Color::White);
    shape.setPosition(x, y);
}

void Paddle::updatePlayer(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) moveUp(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) moveDown(dt);
}

void Paddle::updateAI(float dt, const Ball& ball) {
    float ballY = ball.getPosition().y;
    float centerY = shape.getPosition().y + shape.getSize().y / 2.f;

    if (ballY < centerY) moveUp(dt);
    else if (ballY > centerY) moveDown(dt);
}

void Paddle::render(sf::RenderWindow& window) {
    window.draw(shape);
}

void Paddle::moveUp(float dt) {
    shape.move(0.f, -speed * dt);
}

void Paddle::moveDown(float dt) {
    shape.move(0.f, speed * dt);
}

sf::FloatRect Paddle::getBounds() const {
    return shape.getGlobalBounds();
}

void Paddle::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

sf::Vector2f Paddle::getPosition() const {
    return shape.getPosition();
}
