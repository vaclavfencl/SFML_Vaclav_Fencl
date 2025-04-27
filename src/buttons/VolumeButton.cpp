#include "VolumeButton.h"
#include "../core/SoundManager.h"

VolumeButton::VolumeButton(const sf::Vector2f& size, const sf::Vector2f& position, sf::Font& font)
    : Button(size, position, "", font)
{
    updateLabel();
}

void VolumeButton::onClick() {
    int currentVolume = Settings::volume;
    auto it = std::find(volumeLevels.begin(), volumeLevels.end(), currentVolume);

    if (it != volumeLevels.end() && ++it != volumeLevels.end()) {
        Settings::volume = *it;
    }
    else {
        Settings::volume = volumeLevels.front(); // reset to 0
    }

    SoundManager::setVolume(static_cast<float>(Settings::volume));
    updateLabel();
}

void VolumeButton::updateLabel() {
    label.setString("Volume: " + std::to_string(Settings::volume) + "%");

    sf::FloatRect textRect = label.getLocalBounds();
    label.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    label.setPosition(
        body.getPosition().x + body.getSize().x / 2.f,
        body.getPosition().y + body.getSize().y / 2.f
    );
}
