#include "Button.h"
#include "../core/SoundManager.h"

bool Button::clickSoundLoaded = false;

Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text, sf::Font& font) {
    body.setSize(size);
    body.setPosition(position);
    body.setFillColor(sf::Color::Black);
    body.setOutlineThickness(2.f);
    body.setOutlineColor(sf::Color::White);

    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(24);
    label.setFillColor(sf::Color::White);

    sf::FloatRect textRect = label.getLocalBounds();
    label.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    label.setPosition(
        position.x + size.x / 2.f,
        position.y + size.y / 2.f
    );

    if (!clickSoundLoaded) {
        SoundManager::loadSound("click", "Thirdparty/sounds/click.wav");
        clickSoundLoaded = true;
    }
}

void Button::update(const sf::RenderWindow& window) {
    if (isMouseOver(window)) {
        body.setFillColor(sf::Color(50, 50, 50));
    }
    else {
        body.setFillColor(sf::Color::Black);
    }
}

void Button::render(sf::RenderWindow& window) {
    window.draw(body);
    window.draw(label);
}

bool Button::isMouseOver(const sf::RenderWindow& window) const {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return body.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::playClickSound() {
    SoundManager::playSound("click");
}
