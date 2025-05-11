#pragma once
#include "../core/IGameState.h"
#include "../core/StateHandler.h"
#include "../Game.h"

class GameState : public IGameState {
public:
    GameState(StateHandler& handler, sf::RenderWindow& window);

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    StateHandler& stateHandler;
    Game game;
};