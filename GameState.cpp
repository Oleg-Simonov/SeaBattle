#include "GameState.h"

GameState::GameState(std::stack<State*>* statesPointer, Map* playerMap) : State(statesPointer)
{
	srand(static_cast<unsigned int>(time(0)));
	//init var
	this->dirCounter = 0;
	this->needComeBack = 0;
	this->winFlag = 0;

	this->clickFlags.mouseLeft = false;
	this->clickFlags.againButton = false;
	this->clickFlags.quitButton = false;

	this->playerMap = playerMap;
	//this->playerMap = new Map(100, 100);
	this->playerMove = true;

	//init font
	if (!this->font.loadFromFile("Fonts\\font.ttf"))	std::cout << "Font error" << std::endl; //should be refined

	//init text
	textAboutPlayer.setFont(font);
	textAboutPlayer.setCharacterSize(21);
	textAboutPlayer.setPosition(sf::Vector2f(130, 425));

	textAboutEnemy.setFont(font);
	textAboutEnemy.setCharacterSize(21);
	textAboutEnemy.setPosition(sf::Vector2f(800, 425));

	textInfo.setFont(font);
	textInfo.setCharacterSize(35);
	textInfo.setPosition(sf::Vector2f(535, 45));

	textYourMap.setFont(font);
	textYourMap.setCharacterSize(21);
	textYourMap.setPosition(sf::Vector2f(115, 65));
	textYourMap.setString("Your map:");

	textEnemyMap.setFont(font);
	textEnemyMap.setCharacterSize(21);
	textEnemyMap.setPosition(sf::Vector2f(775, 65));
	textEnemyMap.setString("Enemy's map:");

	//Buttors init
	this->buttons["START_AGAIN"] = new Button(650, 525, 170, 50,
		&this->font, "Start again",
		sf::Color(0, 101, 151, 200), sf::Color(0, 102, 255, 200), sf::Color(0, 0, 255, 200));

	this->buttons["QUIT"] = new Button(900, 525, 170, 50,
		&this->font, "Quit",
		sf::Color(0, 101, 151, 200), sf::Color(0, 102, 255, 200), sf::Color(0, 0, 255, 200));

	//init sounds
	if (!soundBufferMiss.loadFromFile("Resources\\Sounds\\mis.wav")) std::cout << "sound error" << std::endl; //should be refined
	this->soundMiss.setBuffer(soundBufferMiss);
	this->soundMiss.setVolume(30.f);

	if (!soundBufferCrash.loadFromFile("Resources\\Sounds\\crash.wav")) std::cout << "sound error" << std::endl; //should be refined
	this->soundCrash.setBuffer(soundBufferCrash);
	this->soundCrash.setVolume(5.f);

	if (!soundBufferStartGame.loadFromFile("Resources\\Sounds\\StartGame.wav")) std::cout << "sound error" << std::endl; //should be refined
	this->soundStartGame.setBuffer(soundBufferStartGame);
	this->soundStartGame.setVolume(10.f);

	this->soundStartGame.play();
}

GameState::~GameState()
{
	delete this->playerMap;
	for (auto it : this->buttons)
		delete it.second;
}

void GameState::coordCalc()
{
	//filling array with possible coordinates for strike
	nonRepeatVector.clear();
	for (int i = 0; i < this->playerMap->getSizeI() * this->playerMap->getSizeJ(); i++)
	{
		int coorj = i % 10;
		int coori = (i - coorj) / 10;
		int mapValue = this->playerMap->getMapValue(coori, coorj);

		if (mapValue == 0 || mapValue == 1)
			this->nonRepeatVector.push_back(i);
	}

	/*for (int i = 0; i < this->nonRepeatVector.size(); i++)
	{
		std::cout << this->nonRepeatVector[i] << std::endl;
	}*/

	int randomCoor = rand() % this->nonRepeatVector.size();

	coorOfStrike.j = nonRepeatVector[randomCoor] % 10;
	coorOfStrike.i = (nonRepeatVector[randomCoor] - coorOfStrike.j) / 10;

	//nonRepeatVector.clear();
}

void GameState::coordCalc(int coorI, int coorJ)
{
	coorOfStrike.j = coorJ;
	coorOfStrike.i = coorI;
}

void GameState::botAttack(sf::RenderWindow* targetWindow, int coorI, int coorJ)
{
	coordCalc(coorI, coorJ);
	std::cout << "coorOfStrike i = " << coorOfStrike.i << " coorOfStrike j = " << coorOfStrike.j << std::endl;
	switch (this->playerMap->attack(coorI, coorJ))
	{
	case 0:
		std::cout << " Miss! " << std::endl;
		this->playerMove = 1;
		break;
	case 1:
		std::cout << " Damaged! " << std::endl;
		this->damagedDecks.push_back(coorOfStrike);
		break;
	case 2:
		std::cout << " Destroyed! " << std::endl;
		this->damagedDecks.clear();
		break;
	default:
		break;
	}
}

bool GameState::checkField(int coorI, int coorJ) //this function check whether make sense strike into area with coor I, J or not
{
	if (!(coorI < 0 || coorI >= this->playerMap->getSizeI() || coorJ < 0 || coorJ >= this->playerMap->getSizeJ()))
	{
		for (size_t i = 0; i < this->nonRepeatVector.size(); i++)
		{
			//std::cout << this->nonRepeatVector[i] << std::endl;
			if (this->nonRepeatVector[i] == coorI * 10 + coorJ)
				return 1;
		}
	}
	//std::cout << "qwer: " << coorI * 10 + coorJ << std::endl;
	return 0;
}

void GameState::ArtificInt(sf::RenderWindow* targetWindow)
{
	//the first random shot, but we don't shoot in area where we shot before.
	coordCalc();
	if (this->damagedDecks.size() == 0)
	{
		std::cout << " 000 " << std::endl;

		/*if(this->playerMap->getCurrentShipsAmount() == 5)
		coordCalc(5, 7);
		else if (this->playerMap->getCurrentShipsAmount() == 4)
			coordCalc(1, 1);
		else*/
		botAttack(targetWindow, coorOfStrike.i, coorOfStrike.j);
	}
	//the ship has been damaged, we aproximatly know coordinates where could be a deck, we should strike next to it. 
	//In general case, we have four direction for continue attack. Now we should determine direction of ship.
	else if (this->damagedDecks.size() == 1)
	{
		std::cout << " 111 " << std::endl;

		if (checkField(damagedDecks[0].i - 1, damagedDecks[0].j))
			botAttack(targetWindow, damagedDecks[0].i - 1, damagedDecks[0].j);

		else if (checkField(damagedDecks[0].i + 1, damagedDecks[0].j))
			botAttack(targetWindow, damagedDecks[0].i + 1, damagedDecks[0].j);

		else if (checkField(damagedDecks[0].i, damagedDecks[0].j - 1))
			botAttack(targetWindow, damagedDecks[0].i, damagedDecks[0].j - 1);

		else if (checkField(damagedDecks[0].i, damagedDecks[0].j + 1))
			botAttack(targetWindow, damagedDecks[0].i, damagedDecks[0].j + 1);

		else std::cout << "How did it happen?" << std::endl;
	}
	//we've determined direction of the ship. Now we should finish it off.
	else
	{
		std::cout << " 222 " << std::endl;
		int sizeDD = this->damagedDecks.size() - 1;

		//horizontal ship------------------------------------------------------------------------------------
		if (damagedDecks[0].i == damagedDecks[1].i)
		{
			if (checkField(damagedDecks[sizeDD].i, damagedDecks[sizeDD].j - 1))
				botAttack(targetWindow, damagedDecks[sizeDD].i, damagedDecks[sizeDD].j - 1);

			else
			{
				if (checkField(damagedDecks[0].i, damagedDecks[0].j + 1))
					botAttack(targetWindow, damagedDecks[0].i, damagedDecks[0].j + 1);

				else if (checkField(damagedDecks[sizeDD].i, damagedDecks[sizeDD].j + 1))
					botAttack(targetWindow, damagedDecks[sizeDD].i, damagedDecks[sizeDD].j + 1);

				else std::cout << "How did it happen3?" << std::endl;
			}
		}
		//vertical ship--------------------------------------------------------------------------------------
		else if (damagedDecks[0].j == damagedDecks[1].j)
		{
			if (checkField(damagedDecks[sizeDD].i - 1, damagedDecks[sizeDD].j))
				botAttack(targetWindow, damagedDecks[sizeDD].i - 1, damagedDecks[sizeDD].j);
			else
			{

				if (checkField(damagedDecks[0].i + 1, damagedDecks[0].j))
					botAttack(targetWindow, damagedDecks[0].i + 1, damagedDecks[0].j);

				else if (checkField(damagedDecks[sizeDD].i + 1, damagedDecks[sizeDD].j))
					botAttack(targetWindow, damagedDecks[sizeDD].i + 1, damagedDecks[sizeDD].j);

				else std::cout << "How did it happen4?" << std::endl;
			}
		}
		else std::cout << "How did it happen6?" << std::endl;
	}
}



void GameState::update(sf::RenderWindow* targetWindow)
{
	if (enemyMap.getCurrentShipsAmount() > 0 && playerMap->getCurrentShipsAmount() > 0)
	{
		if (this->playerMove == false)
		{
			this->textInfo.setString("Enemy's move");
			if (clock.getElapsedTime().asSeconds() > 0.1)
			{
				ArtificInt(targetWindow);
				this->clock.restart();
			}
		}
		else this->textInfo.setString("You move");

		
		//mouse poll----------------------------------------------------
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->clickFlags.mouseLeft)
		{
			this->clock.restart();
			//std::cout << this->nonRepeatRandNumber() << std::endl;
			if (this->playerMove)
			{
				int number = this->enemyMap.determinationChosenMapField(targetWindow);
				
				int coorJ = number % 10;
				int coorI = (number - coorJ) / 10;

				int result = this->enemyMap.attack(coorI, coorJ);
				this->playerMove = result;

				if (result == 1 || result == 2) this->soundCrash.play();
				else if (result == 0) this->soundMiss.play(); 

				this->enemyMap.getMapValue();
				
			}


			this->clickFlags.mouseLeft = true;
		}

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->clickFlags.mouseLeft)
		{
			this->clickFlags.mouseLeft = false;
		}

		//Text update------------------------------------------------------
		std::stringstream ss;
		ss << "Enemy ships remain: " << enemyMap.getCurrentShipsAmount() << " out of " << enemyMap.getShipsAmount() << "\n";

		/*for (int i = 0; i < enemyMap.getShipsAmount(); i++)
		{
			ss << "Enemy ship " << i + 1 << " HP: " << (enemyMap.getShips() + i)->getShipHp() << " out of " << (enemyMap.getShips() + i)->getDeckAmount() << "\n";
		}*/
			/*<< "Enemy ship " << 0 << " HP: " << enemyMap.getShips()->getShipHp() << " out of " << enemyMap.getShips()->getDeckAmount() << "\n"
			<< "Enemy ship " << 1 << " HP: " << (enemyMap.getShips() + 1)->getShipHp() << " out of " << (enemyMap.getShips() + 1)->getDeckAmount() << "\n"
			<< "Enemy ship " << 2 << " HP: " << (enemyMap.getShips() + 2)->getShipHp() << " out of " << (enemyMap.getShips() + 2)->getDeckAmount() << "\n"
			<< "Enemy ship " << 3 << " HP: " << (enemyMap.getShips() + 3)->getShipHp() << " out of " << (enemyMap.getShips() + 3)->getDeckAmount() << "\n"
			<< "Enemy ship " << 4 << " HP: " << (enemyMap.getShips() + 4)->getShipHp() << " out of " << (enemyMap.getShips() + 4)->getDeckAmount() << "\n"
			;*/
		this->textAboutEnemy.setString(ss.str());

		ss.str("");
		ss << "Your ships remain: " << playerMap->getCurrentShipsAmount() << " out of " << playerMap->getShipsAmount() << "\n";
		this->textAboutPlayer.setString(ss.str());

		//std::cout << sf::Mouse::getPosition(*targetWindow).x << "   " << sf::Mouse::getPosition(*targetWindow).y << std::endl;

		enemyMap.updateMap(targetWindow, 1);
		playerMap->updateMap(targetWindow);
	}
	else if (enemyMap.getCurrentShipsAmount() <= 0 && this->winFlag == 0)
	{
		this->textInfo.setString("YOU WIN!");
		if (!soundBufferWin.loadFromFile("Resources\\Sounds\\win.wav")) std::cout << "sound error" << std::endl; //should be refined
		this->soundWin.setBuffer(soundBufferWin);
		this->soundWin.setVolume(15.f);
		this->soundWin.play();
		this->winFlag = 1;
	}
	else if(this->winFlag == 0)
	{
		this->textInfo.setString("YOU LOSE!");
		if (!soundBufferLose.loadFromFile("Resources\\Sounds\\Lose.wav")) std::cout << "sound error" << std::endl; //should be refined
		this->soundLose.setBuffer(soundBufferLose);
		this->soundLose.setVolume(15.f);
		this->soundLose.play();
		this->winFlag = 1;
	}


	if (buttons["START_AGAIN"]->isPressed() && !this->clickFlags.againButton)
	{
		this->endState = 2;
		//std::cout << "STartgain = " << endState << std::endl;
		this->clickFlags.againButton = true;
	}

	if (!buttons["START_AGAIN"]->isPressed() && this->clickFlags.againButton)
	{
		this->clickFlags.againButton = false;
	}

	if (buttons["QUIT"]->isPressed() && !this->clickFlags.againButton)
	{
		this->endState = 3;
		this->clickFlags.againButton = true;
	}

	if (!buttons["QUIT"]->isPressed() && this->clickFlags.againButton)
	{
		this->clickFlags.againButton = false;
	}

	this->mouseUpdatePosition(targetWindow);

	for (auto it : this->buttons)
		it.second->update(sf::Vector2f((float)this->mousePosWindow.x, (float)this->mousePosWindow.y));
}

void GameState::render(sf::RenderWindow* targetWindow)
{
	targetWindow->draw(this->backgroundSprite);
	targetWindow->draw(textAboutPlayer);
	targetWindow->draw(textAboutEnemy);
	targetWindow->draw(textYourMap);
	targetWindow->draw(textEnemyMap);
	targetWindow->draw(textInfo);

	playerMap->renderMap(targetWindow);
	enemyMap.renderMap(targetWindow);

	for (auto it : this->buttons)
		it.second->render(targetWindow);

	this->legend.render(targetWindow);
}

GameState::CoordinatesOfStrike::CoordinatesOfStrike()
{
	this->i = 1000;
	this->j = 1000;
}

GameState::CoordinatesOfStrike::CoordinatesOfStrike(int i, int j)
{
	this->i = i;
	this->j = j;
}
