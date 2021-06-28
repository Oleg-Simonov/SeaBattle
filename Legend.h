#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

class Legend
{
private:
    sf::Font font;
    sf::Text textLegend;
    sf::Text textLegendHeader;

    sf::RectangleShape unexploredField, emptyField, deckOfShip, destrDeck, bound;

public:
    Legend(int x, int y);
    ~Legend();

    void update(sf::RenderWindow* targetWindow);
    void render(sf::RenderWindow* targetWindow);
};

