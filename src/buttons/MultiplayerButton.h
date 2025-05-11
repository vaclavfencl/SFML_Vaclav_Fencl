#pragma once
#include "Button.h"
#include "../core/StateHandler.h"
#include <SFML/Graphics.hpp>

class MultiplayerButton : public Button {
public:
    MultiplayerButton(const sf::Vector2f& size, const sf::Vector2f& position, sf::Font& font, StateHandler& handler, sf::RenderWindow& window);

    void onClick() override;

private:
    StateHandler& stateHandler;
    sf::RenderWindow& window;
};
