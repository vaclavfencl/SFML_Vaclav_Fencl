#pragma once
#ifndef RESUMEBUTTON_H
#define RESUMEBUTTON_H

#include "Button.h"
#include "../core/StateHandler.h"

class ResumeButton : public Button {
public:
    ResumeButton(const sf::Vector2f& size, const sf::Vector2f& position, sf::Font& font, StateHandler& handler);

    void onClick() override;

private:
    StateHandler& stateHandler;
};

#endif
