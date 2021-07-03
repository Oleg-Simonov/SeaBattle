#include "GameState.h"

GameState::GameState(std::vector<State*>* statesPointer, Map* playerMap) : State(statesPointer)
{
	srand(static_cast<unsigned int>(time(0)));
	//init var
	this->winFlag = 0;

	this->playerMap = playerMap;
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
	//delete this->playerMap; why???

	for (auto it : this->buttons)
		delete it.second;
}

void GameState::botAttack(int i, int j)
{
	//coordCalc(botAttackCoord.i, botAttackCoord.j);
#ifdef DEBUG_GAMESTATE
	std::cout << "coorOfStrike i = " << i << " coorOfStrike j = " << j << std::endl;
#endif // DEBUG

	switch (this->playerMap->attack(MapCoord(i, j)))
	{
	case 0:
#ifdef DEBUG_GAMESTATE
		std::cout << " Miss! " << std::endl;
#endif
		this->playerMove = 1;
		break;
	case 1:
#ifdef DEBUG_GAMESTATE
		std::cout << " Damaged! " << std::endl;
#endif
		this->damagedDecks.push_back(MapCoord(i, j));
		break;
	case 2:
#ifdef DEBUG_GAMESTATE
		std::cout << " Destroyed! " << std::endl;
#endif
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

	//the first random shot, but we don't shoot in area where we shot before.
	if (this->damagedDecks.size() == 0)
	{
#ifdef DEBUG_GAMESTATE
		std::cout << " 000 " << std::endl;
#endif
		//botAttack(this->botAttackCoord);
		int randomCoor = rand() % this->nonRepeatVector.size();
		int coordJ = nonRepeatVector[randomCoor] % 10;
		int coordI = (nonRepeatVector[randomCoor] - coordJ) / 10;

		botAttack(coordI, coordJ);
	}
	//the ship has been damaged, we aproximatly know coordinates where could be a deck, we should strike next to it. 
	//In general case, we have four direction for continue attack. Now we should determine direction of ship.
	else if (this->damagedDecks.size() == 1)
	{
#ifdef DEBUG_GAMESTATE
		std::cout << " 111 " << std::endl;
#endif
		
		if (checkField(damagedDecks[0].i - 1, damagedDecks[0].j))
			botAttack(damagedDecks[0].i - 1, damagedDecks[0].j);

		else if (checkField(damagedDecks[0].i + 1, damagedDecks[0].j))
			botAttack(damagedDecks[0].i + 1, damagedDecks[0].j);

		else if (checkField(damagedDecks[0].i, damagedDecks[0].j - 1))
			botAttack(damagedDecks[0].i, damagedDecks[0].j - 1);

		else if (checkField(damagedDecks[0].i, damagedDecks[0].j + 1))
			botAttack(damagedDecks[0].i, damagedDecks[0].j + 1);
#ifdef DEBUG_GAMESTATE
		else std::cout << "How did it happen?" << std::endl;
#endif
	}
	//we've determined direction of the ship. Now we should finish it off.
	else
	{
#ifdef DEBUG_GAMESTATE
		std::cout << " 222 " << std::endl;
#endif
		int sizeDD = this->damagedDecks.size() - 1;

		//horizontal ship------------------------------------------------------------------------------------
		if (damagedDecks[0].i == damagedDecks[1].i)
		{
			if (checkField(damagedDecks[sizeDD].i, damagedDecks[sizeDD].j - 1))
				botAttack(damagedDecks[sizeDD].i, damagedDecks[sizeDD].j - 1);

			else
			{
				if (checkField(damagedDecks[0].i, damagedDecks[0].j + 1))
					botAttack(damagedDecks[0].i, damagedDecks[0].j + 1);

				else if (checkField(damagedDecks[sizeDD].i, damagedDecks[sizeDD].j + 1))
					botAttack(damagedDecks[sizeDD].i, damagedDecks[sizeDD].j + 1);
#ifdef DEBUG_GAMESTATE
				else std::cout << "How did it happen3?" << std::endl;
#endif
			}
		}
		//vertical ship--------------------------------------------------------------------------------------
		else if (damagedDecks[0].j == damagedDecks[1].j)
		{
			if (checkField(damagedDecks[sizeDD].i - 1, damagedDecks[sizeDD].j))
				botAttack(damagedDecks[sizeDD].i - 1, damagedDecks[sizeDD].j);

			else
			{
				if (checkField(damagedDecks[0].i + 1, damagedDecks[0].j))
					botAttack(damagedDecks[0].i + 1, damagedDecks[0].j);

				else if (checkField(damagedDecks[sizeDD].i + 1, damagedDecks[sizeDD].j))
					botAttack(damagedDecks[sizeDD].i + 1, damagedDecks[sizeDD].j);
#ifdef DEBUG_GAMESTATE
				else std::cout << "How did it happen4?" << std::endl;
#endif
			}
		}
#ifdef DEBUG_GAMESTATE
		else std::cout << "How did it happen6?" << std::endl;
#endif
	}
}



void GameState::update(sf::RenderWindow* targetWindow)
{
	for (auto it : this->buttons)
		it.second->update(sf::Vector2f((float)this->mousePosWindow.x, (float)this->mousePosWindow.y));

	enemyMap.updateMap(targetWindow, 1);
	playerMap->updateMap(targetWindow);

	while (targetWindow->pollEvent(sfEvent))
	{
		if (this->sfEvent.type == sf::Event::EventType::Closed)
			targetWindow->close();

		else if (this->sfEvent.type == sfEvent.MouseButtonPressed && this->sfEvent.mouseButton.button == sf::Mouse::Button::Left)
		{
			this->clock.restart();
			//std::cout << this->nonRepeatRandNumber() << std::endl;
			if (this->playerMove && enemyMap.getCurrentShipsAmount() > 0 && playerMap->getCurrentShipsAmount() > 0)
			{
				int result = this->enemyMap.attack(this->enemyMap.getChosenField());
				this->playerMove = result;

				if (result == 1 || result == 2) this->soundCrash.play();
				else if (result == 0) this->soundMiss.play();
#ifdef DEBUG_GAMESTATE
				this->enemyMap.getMapValue(); 
#endif
			}

			if (buttons["START_AGAIN"]->isPressed())
				this->endState = 1;

			if (buttons["QUIT"]->isPressed())
				this->endState = -1;
		}

	}

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

	//Text update------------------------------------------------------
	std::stringstream ss;
	ss << "Enemy ships remain: " << enemyMap.getCurrentShipsAmount() << " out of " << enemyMap.getShipsAmount() << "\n";
	this->textAboutEnemy.setString(ss.str());
	ss.str("");
	ss << "Your ships remain: " << playerMap->getCurrentShipsAmount() << " out of " << playerMap->getShipsAmount() << "\n";
	this->textAboutPlayer.setString(ss.str());

	this->mouseUpdatePosition(targetWindow);
}

void GameState::render(sf::RenderWindow* targetWindow)
{
	targetWindow->draw(this->backgroundSprite);
	targetWindow->draw(textAboutPlayer);
	targetWindow->draw(textAboutEnemy);
	targetWindow->draw(textInfo);

	playerMap->renderMap(targetWindow);
	enemyMap.renderMap(targetWindow);

	for (auto it : this->buttons)
		it.second->render(targetWindow);

	this->legend.render(targetWindow);
}
