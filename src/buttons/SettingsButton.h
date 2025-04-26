#pragma once
#include "Button.h"
#include "../core/StateHandler.h"
#include "../states/SettingsState.h"

class SettingsButton : public Button {
public:
    SettingsButton(const sf::Vector2f& size, const sf::Vector2f& position, sf::Font& font, StateHandler& handler, sf::RenderWindow& window);

    void onClick() override;

private:
    StateHandler& stateHandler;
    sf::RenderWindow& window;
};
