#pragma once
#include <Map>
#include <string>
#include "State.h"
#include "GameState.h"

class PlacingState :
    public State
{
private:
    sf::Font font;
    sf::Text infoText;
    Map playerMap;

    std::map<std::string, Button*> buttons2;

    struct ClickFlags
    {
        bool mouseLeft;
        bool space;
        bool startButton;
        bool againlButton;
        bool toMainMenuButton;
    };

    ClickFlags clickFlags;

    std::vector<OutMapShip> outMapShip;
public:

    PlacingState(std::stack<State*>* statesPointer);
    ~PlacingState();

    void update(sf::RenderWindow* targetWindow = nullptr);
    void render(sf::RenderWindow* targetWindow = nullptr);
};