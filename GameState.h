#pragma once
#include "State.h"
#include <cstdlib> // для функций rand() и srand()
#include <ctime> // для функции time()
#include <algorithm>
#include <list>

class CoordinatesOfStrike;

class GameState :
    public State
{
private:
    sf::Font font;
    sf::Text infoText;
    Map enemyMap = Map(1);
    Map* playerMap;

    bool playerMove;
    int dirCounter;
    int needComeBack;

    std::vector<OutMapShip> outMapShip;
    std::vector<int> nonRepeatVector;
    std::vector<std::vector<int>> knownFields;

    class CoordinatesOfStrike
    {
    public:
        int i, j;
        CoordinatesOfStrike();
        CoordinatesOfStrike(int i, int j);
    };

    struct ClickFlags
    {
        bool mouseLeft;
    };

    ClickFlags clickFlags;
    CoordinatesOfStrike coorOfStrike;
    std::vector<CoordinatesOfStrike> damagedDecks;
    
public:

    GameState(std::stack<State*>* statesPointer, Map* playerMap = nullptr);
    ~GameState();

    void coordCalc();
    void coordCalc(int coorI, int coorJ);
    void botAttack(sf::RenderWindow* targetWindow, int coorI, int coorJ);
    bool checkField(int coorI, int coorJ);
    void ArtificInt(sf::RenderWindow* targetWindow);
    void update(sf::RenderWindow* targetWindow = nullptr);
    void render(sf::RenderWindow* targetWindow = nullptr);
};

