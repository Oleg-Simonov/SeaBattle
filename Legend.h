#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <windows.h>

class Legend
{
private:
    sf::Font font;
    sf::Text textLegend;
    sf::Text textLegendHeader;

    sf::RectangleShape unexploredField, emptyField, deckOfShip, destrDeck, bound;

public:
    Legend(float x, float y);
    ~Legend();

    void update(sf::RenderWindow* targetWindow);
    void render(sf::RenderWindow* targetWindow);
};

