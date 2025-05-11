#pragma once

#include "../core/IGameState.h"
#include "../core/StateHandler.h"
#include "../buttons/Button.h"
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class MultiplayerState : public IGameState {
public:
    MultiplayerState(StateHandler& handler, sf::RenderWindow& window);

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    StateHandler& stateHandler;
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text statusText;

    std::vector<std::unique_ptr<Button>> buttons;
    sf::TcpListener listener;
    sf::TcpSocket socket;

    sf::SocketSelector selector;
    bool clientConnected = false;

    sf::Clock connectionClock;
    const sf::Time connectTimeout = sf::seconds(10);
    
    sf::Clock hostSendClock;
    sf::Clock clientSendClock;
    sf::Clock receiveClock;

    bool isHosting = false;
    bool isConnecting = false;
    bool isConnected = false;

    void onHostPressed();
    void onConnectPressed();
};
