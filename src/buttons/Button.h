#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
public:
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text, sf::Font& font);
    virtual ~Button() = default;

    virtual void update(const sf::RenderWindow& window);
    virtual void render(sf::RenderWindow& window);
    virtual void onClick() = 0;

    bool isMouseOver(const sf::RenderWindow& window) const;
    static void playClickSound();

protected:
    static bool clickSoundLoaded;

    sf::RectangleShape body;
    sf::Text label;
};

#endif
