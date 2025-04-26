#pragma once
#include "../core/IGameState.h"
#include "../core/StateHandler.h"
#include <SFML/Graphics.hpp>

class SettingsState : public IGameState {
public:
    SettingsState(StateHandler& handler, sf::RenderWindow& window);

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    StateHandler& stateHandler;
    sf::Font font;
    sf::Text infoText;
};
