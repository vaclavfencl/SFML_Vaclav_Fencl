#include "HostButton.h"

HostButton::HostButton(const sf::Vector2f& size, const sf::Vector2f& position, sf::Font& font,
    std::function<void()> callback)
    : Button(size, position, "Host", font), callback(callback) {}

void HostButton::onClick() {
    if (callback) callback();
}
