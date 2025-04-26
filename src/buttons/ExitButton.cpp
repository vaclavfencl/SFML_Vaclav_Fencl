#include "ExitButton.h"

ExitButton::ExitButton(const sf::Vector2f& size, const sf::Vector2f& position, sf::Font& font, sf::RenderWindow& window)
    : Button(size, position, "Exit", font), window(window) {}

void ExitButton::onClick() {
    window.close();
}
