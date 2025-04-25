#include "Paddle.h"

Paddle::Paddle(float x, float y, float screenHeight) : screenHeight(screenHeight) {
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
    if (shape.getPosition().y > 0.f)
        shape.move(0.f, -speed * dt);

    if (shape.getPosition().y < 0.f)
        shape.setPosition(shape.getPosition().x, 0.f);
}

void Paddle::moveDown(float dt) {
    float bottom = shape.getPosition().y + shape.getSize().y;
    if (bottom < screenHeight)
        shape.move(0.f, speed * dt);

    if (shape.getPosition().y + shape.getSize().y > screenHeight)
        shape.setPosition(shape.getPosition().x, screenHeight - shape.getSize().y);
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

sf::Vector2f Paddle::getSize() const {
    return shape.getSize();
}
