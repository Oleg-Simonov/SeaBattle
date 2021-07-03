#pragma once
#include "State.h"
#include "Legend.h"
#include <cstdlib> // для функций rand() и srand()
#include <ctime> // для функции time()
#include <algorithm>
//#define DEBUG_GAMESTATE

//class CoordinatesOfStrike;

class GameState :
    public State
{
private:
    sf::SoundBuffer soundBufferMiss;
    sf::SoundBuffer soundBufferCrash;
    sf::SoundBuffer soundBufferStartGame;
    sf::SoundBuffer soundBufferWin;
    sf::SoundBuffer soundBufferLose;

    sf::Sound soundMiss;
    sf::Sound soundCrash;
    sf::Sound soundStartGame;
    sf::Sound soundWin;
    sf::Sound soundLose;

    sf::Font font;
    sf::Text textAboutPlayer;
    sf::Text textAboutEnemy;
    sf::Text textInfo;

    Legend legend = Legend(100, 500);

    Map enemyMap = Map(770, 100, 1);
    Map* playerMap;

    bool winFlag;
    bool playerMove;

    std::map<std::string, Button*> buttons;
    std::vector<int> nonRepeatVector;
    std::vector<MapCoord> damagedDecks;
    
public:

    GameState(std::vector<State*>* statesPointer, Map* playerMap = nullptr);
    ~GameState();

    void botAttack(int i, int j);
    bool checkField(int coorI, int coorJ);
    void ArtificInt(sf::RenderWindow* targetWindow);
    void update(sf::RenderWindow* targetWindow = nullptr);
    void render(sf::RenderWindow* targetWindow = nullptr);
};

