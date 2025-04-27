#pragma once
#ifndef FULLSCREENBUTTON_H
#define FULLSCREENBUTTON_H

#include "Button.h"
#include "../core/Settings.h"

class FullscreenButton : public Button {
public:
    FullscreenButton(const sf::Vector2f& size, const sf::Vector2f& position, sf::Font& font);

    void onClick() override;
    void updateLabel();
};

#endif
