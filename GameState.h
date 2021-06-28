#pragma once
#include "State.h"
#include "Legend.h"
#include <cstdlib> // для функций rand() и srand()
#include <ctime> // для функции time()
#include <algorithm>
#include <SFML/Audio.hpp>

class CoordinatesOfStrike;

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
    sf::Text textYourMap;
    sf::Text textEnemyMap;

    Legend legend = Legend(100, 500);

    Map enemyMap = Map(770, 100, 1);
    Map* playerMap;

    bool winFlag;
    bool playerMove;
    int dirCounter;
    int needComeBack;

    struct ClickFlags
    {
        bool mouseLeft;
        bool againButton;
        bool quitButton;
    };

    ClickFlags clickFlags;
    std::map<std::string, Button*> buttons;
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

