#include "Apple.h"

Apple::Apple() {
    shape.setRadius(20.0f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(435.f, 320.f);
}

void Apple::update(float deltaTime) {
    handleInput();
}

void Apple::render(sf::RenderWindow& window) {
    window.draw(shape);
}
