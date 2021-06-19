#pragma once
#include <Map>
#include <string>
#include <sstream>
#include "State.h"
#include "GameState.h"

class PlacingState :
    public State
{
private:
    sf::Font font;
    sf::Text headerText;
    sf::Text helpText;
    sf::Text yourMapText;
    sf::Text yourShipsText;
    Map playerMap = Map(30, 100);

    std::vector<sf::RectangleShape> outMapShipsTable;

    //int deck1, deck2, deck3, deck4, deck5;

    std::map<std::string, Button*> buttons2;

    struct ClickFlags
    {
        bool mouseLeft;
        bool space;
        bool startButton;
        bool randomButton;
        bool againlButton;
        bool toMainMenuButton;
    };

    ClickFlags clickFlags;

    std::vector<OutMapShip> outMapShip;
    std::vector<int> nonRepeatVector;

public:

    PlacingState(std::stack<State*>* statesPointer);
    ~PlacingState();

    void update(sf::RenderWindow* targetWindow = nullptr);
    void render(sf::RenderWindow* targetWindow = nullptr);
};