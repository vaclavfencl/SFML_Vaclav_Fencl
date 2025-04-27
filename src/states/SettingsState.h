#pragma once
#include "../core/IGameState.h"
#include "../core/StateHandler.h"
#include "../buttons/BackButton.h"
#include "../buttons/VolumeButton.h"
#include "../buttons/FullscreenButton.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

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
    sf::RenderWindow& window;
    std::unique_ptr<BackButton> backButton;
    std::vector<std::unique_ptr<Button>> optionButtons;
};
