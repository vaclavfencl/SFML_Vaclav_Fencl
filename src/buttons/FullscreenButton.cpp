#include "FullscreenButton.h"

FullscreenButton::FullscreenButton(const sf::Vector2f& size, const sf::Vector2f& position, sf::Font& font)
    : Button(size, position, "", font)
{
    updateLabel();
}

void FullscreenButton::onClick() {
    Settings::fullscreen = !Settings::fullscreen;
    Settings::needsWindowReload = true;
    updateLabel();
}

void FullscreenButton::updateLabel() {
    label.setString("Fullscreen: " + std::string(Settings::fullscreen ? "ON" : "OFF"));

    sf::FloatRect textRect = label.getLocalBounds();
    label.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    label.setPosition(
        body.getPosition().x + body.getSize().x / 2.f,
        body.getPosition().y + body.getSize().y / 2.f
    );
}
