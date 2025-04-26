#pragma once
#include "Button.h"

class ExitButton : public Button {
public:
    ExitButton(const sf::Vector2f& size, const sf::Vector2f& position, sf::Font& font, sf::RenderWindow& window);

    void onClick() override;

private:
    sf::RenderWindow& window;
};
