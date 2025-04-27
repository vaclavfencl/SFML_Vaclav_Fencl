#pragma once
#ifndef VOLUMEBUTTON_H
#define VOLUMEBUTTON_H

#include "Button.h"
#include "../core/Settings.h"

class VolumeButton : public Button {
public:
    VolumeButton(const sf::Vector2f& size, const sf::Vector2f& position, sf::Font& font);

    void onClick() override;
    void updateLabel();

private:
    std::vector<int> volumeLevels = { 0, 25, 50, 75, 100 };
};

#endif
