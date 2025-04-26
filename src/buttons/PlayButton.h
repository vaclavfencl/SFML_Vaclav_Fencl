#pragma once
#include "Button.h"
#include "../core/StateHandler.h"
#include "../states/GameState.h"

class PlayButton : public Button {
public:
    PlayButton(const sf::Vector2f& size, const sf::Vector2f& position, sf::Font& font, StateHandler& handler, sf::RenderWindow& window);

    void onClick() override;

private:
    StateHandler& stateHandler;
    sf::RenderWindow& window;
};
