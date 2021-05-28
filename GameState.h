#pragma once
#include "State.h"

class GameState :
    public State
{
private:
    sf::Font font;
    sf::Text infoText;
    Map playerMap, enemyMap = Map(1);
    bool mouseLeftFrontEdge;
    bool spaceFrontEdge, spaceBackEdge;

    std::vector<OutMapShip> outMapShip;
public:

    GameState(std::stack<State*>* statesPointer);
    ~GameState();

    void update(sf::RenderWindow* targetWindow = nullptr);
    void render(sf::RenderWindow* targetWindow = nullptr);
};

