#include "Paddle.h"

Paddle::Paddle(float x, float y, float screenHeight) : screenHeight(screenHeight) {
    rectShape.setSize(sf::Vector2f(20.f, 100.f));
    rectShape.setFillColor(sf::Color::White);
    rectShape.setPosition(x, y);
    shape = &rectShape;  
}

void Paddle::updatePlayer(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) moveUp(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) moveDown(dt);
}

void Paddle::updateAI(float dt, const Ball& ball) {
    float ballY = ball.getPosition().y;
    float centerY = getPosition().y + rectShape.getSize().y / 2.f;

    if (ballY < centerY) moveUp(dt);
    else if (ballY > centerY) moveDown(dt);
}

void Paddle::moveUp(float dt) {
    if (getPosition().y > 0.f)
        shape->move(0.f, -speed * dt);

    if (getPosition().y < 0.f)
        setPosition(getPosition().x, 0.f);
}

void Paddle::moveDown(float dt) {
    float bottom = getPosition().y + rectShape.getSize().y;
    if (bottom < screenHeight)
        shape->move(0.f, speed * dt);

    if (getPosition().y + rectShape.getSize().y > screenHeight)
        setPosition(getPosition().x, screenHeight - rectShape.getSize().y);
}

sf::Vector2f Paddle::getSize() const {
    return rectShape.getSize();
}
