#include "ConnectButton.h"

ConnectButton::ConnectButton(const sf::Vector2f& size, const sf::Vector2f& position, sf::Font& font,
    std::function<void()> callback)
    : Button(size, position, "Connect", font), callback(callback) {}

void ConnectButton::onClick() {
    if (callback) callback();
}
