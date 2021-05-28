#pragma once
#include "State.h"
#include "PlacingState.h"

class MainMenuState :
    public State
{
private:
    sf::Font font;
    sf::Text infoText;
    sf::Vector2f infoTextPos;
    

    std::map<std::string, Button*> buttons;

    struct ClickFlags
    {
        bool mouseLeft;
        bool singleButton;
        bool multiplButton;
        bool optionButton;
        bool quitButton;
    };

    ClickFlags clickFlags;

public:
    MainMenuState(std::stack<State*>* statesPointer);
    ~MainMenuState();

   
    void update(sf::RenderWindow* targetWindow = nullptr);
    void render(sf::RenderWindow* targetWindow = nullptr);
};

