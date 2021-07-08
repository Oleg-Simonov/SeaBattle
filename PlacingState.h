#pragma once
#include <Map>
#include <string>
#include "State.h"
#include "GameState.h"
#include <windows.h>

class PlacingState :
    public State
{
private:
    sf::SoundBuffer soundBufferPlacing;
    sf::Sound soundPlacing;
    sf::SoundBuffer soundBufferFlipShip;
    sf::Sound soundFlipShip;

    sf::Font font;
    sf::Text headerText;
    sf::Text helpText;
    sf::Text yourShipsText;

    sf::RectangleShape helpTextBackground;

    Map playerMap = Map(110, 100);

    std::vector<sf::RectangleShape> outMapShipsTable;

    std::map<std::string, Button*> buttons;

    std::vector<OutMapShip> outMapShip;

public:

    PlacingState(std::vector<State*>* statesPointer);
    ~PlacingState();

    void initOutMapShips();

    void update(sf::RenderWindow* targetWindow = nullptr);
    void render(sf::RenderWindow* targetWindow = nullptr);
};