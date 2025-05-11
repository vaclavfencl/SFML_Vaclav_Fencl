#pragma once
#pragma once

#include "Button.h"
#include "../core/StateHandler.h"
#include <SFML/Graphics.hpp>
#include <functional>

class ConnectButton : public Button {
public:
    ConnectButton(const sf::Vector2f& size, const sf::Vector2f& position, sf::Font& font,
        std::function<void()> callback);

    void onClick() override;

private:
    std::function<void()> callback;
};
