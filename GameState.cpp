#include "GameState.h"

GameState::GameState(std::vector<State*>* statesPointer, Map* playerMap) : State(statesPointer)
{
	srand(static_cast<unsigned int>(time(0)));

	//init var
	this->winFlag = 0;

	this->playerMap = playerMap;
	
	this->playerMove = rand() % 2; //who go first we choose randomly

	//init font
	if (!this->font.loadFromFile("Fonts\\font.ttf"))	MessageBox(0, (LPCWSTR)L"Font error GameState", (LPCWSTR)L"Error message", 0);

	//init text
	textAboutPlayer.setFont(font);
	textAboutPlayer.setCharacterSize(21);
	textAboutPlayer.setPosition(sf::Vector2f(130, 425));

	textAboutEnemy.setFont(font);
	textAboutEnemy.setCharacterSize(21);
	textAboutEnemy.setPosition(sf::Vector2f(800, 425));

	textInfo.setFont(font);
	textInfo.setCharacterSize(35);
	textInfo.setPosition(sf::Vector2f(515, 45));

	//Buttors init
	this->buttons["START_AGAIN"] = new Button(650, 525, 170, 50,
		&this->font, "Start again",
		sf::Color(0, 101, 151, 200), sf::Color(0, 102, 255, 200), sf::Color(0, 0, 255, 200));

	this->buttons["QUIT"] = new Button(900, 525, 170, 50,
		&this->font, "Quit",
		sf::Color(0, 101, 151, 200), sf::Color(0, 102, 255, 200), sf::Color(0, 0, 255, 200));

	//init sounds
	if (!soundBufferMiss.loadFromFile("Resources\\Sounds\\mis.wav")) MessageBox(0, (LPCWSTR)L"Sound soundBufferMiss error", (LPCWSTR)L"Error message", 0);
	this->soundMiss.setBuffer(soundBufferMiss);
	this->soundMiss.setVolume(30.f);

	if (!soundBufferCrash.loadFromFile("Resources\\Sounds\\crash.wav")) MessageBox(0, (LPCWSTR)L"Sound soundBufferCrash error", (LPCWSTR)L"Error message", 0);
	this->soundCrash.setBuffer(soundBufferCrash);
	this->soundCrash.setVolume(5.f);

	if (!soundBufferStartGame.loadFromFile("Resources\\Sounds\\StartGame.wav")) MessageBox(0, (LPCWSTR)L"Sound soundBufferStartGame error", (LPCWSTR)L"Error message", 0);
	this->soundStartGame.setBuffer(soundBufferStartGame);
	this->soundStartGame.setVolume(10.f);

	if (!soundBufferWin.loadFromFile("Resources\\Sounds\\win.wav")) MessageBox(0, (LPCWSTR)L"Sound soundBufferWin error", (LPCWSTR)L"Error message", 0);
	this->soundWin.setBuffer(soundBufferWin);
	this->soundWin.setVolume(15.f);

	if (!soundBufferLose.loadFromFile("Resources\\Sounds\\Lose.wav")) MessageBox(0, (LPCWSTR)L"Sound soundBufferLose error", (LPCWSTR)L"Error message", 0);
	this->soundLose.setBuffer(soundBufferLose);
	this->soundLose.setVolume(15.f);

	this->soundStartGame.play();
}

GameState::~GameState()
{
	for (auto it : this->buttons)
		delete it.second;
}

void GameState::botAttack(int i, int j)
{
	//coordCalc(botAttackCoord.i, botAttackCoord.j);
	//std::cout << "coorOfStrike i = " << i << " coorOfStrike j = " << j << std::endl;
	switch (this->playerMap->attack(MapCoord(i, j)))
	{
	case 0:
		//std::cout << " Miss! " << std::endl;
		this->playerMove = 1;
		break;
	case 1:
		//std::cout << " Damaged! " << std::endl;
		this->damagedDecks.push_back(MapCoord(i, j));
		break;
	case 2:
		//std::cout << " Destroyed! " << std::endl;
		this->damagedDecks.clear();
		break;
	default:
		break;
	}
}

bool GameState::checkField(int coorI, int coorJ) //this function check whether make sense strike into area with coor I, J or not
{
	std::vector<sf::Vector2i> coordForAttack;
	for (int i = 0; i < this->playerMap->getSizeI() * this->playerMap->getSizeJ(); i++)
	{
		int coorj = i % 10;
		int coori = (i - coorj) / 10;
		int mapValue = this->playerMap->getMapValue(coori, coorj);

		if (mapValue == 0 || mapValue == 1)
			coordForAttack.emplace_back(coori, coorj);
	}

	if (!(coorI < 0 || coorI >= this->playerMap->getSizeI() || coorJ < 0 || coorJ >= this->playerMap->getSizeJ()))
	{
		for (size_t i = 0; i < coordForAttack.size(); i++)
		{
			if (coordForAttack[i] == sf::Vector2i(coorI, coorJ)/*coorI * 10 + coorJ*/)
				return 1;
		}
	}
//std::cout << "qwer: " << coorI * 10 + coorJ << std::endl;
	return 0;
}

void GameState::ArtificInt()
{
	//The most efficency strategy is first of all to destroy the biggest ship
	if (this->damagedDecks.size() == 0)
	{
		//searching for the biggest ship among living ship
		//assume that the biggest ship is the first alive ship in the array
		int indexOfShipWithMaxDack = 0;
		for (size_t i = 0; i < this->playerMap->getShips().size(); i++)
		{
			if (this->playerMap->getShips()[i].getShipHp() > 0)
			{
				indexOfShipWithMaxDack = i;
				break;
			}
		}

		//search the biggest element
		for (size_t i = 0; i < this->playerMap->getShips().size(); i++)
		{
			if (this->playerMap->getShips()[i].getShipHp() > 0)
			{
				if (this->playerMap->getShips()[i].getDeckAmount() > this->playerMap->getShips()[indexOfShipWithMaxDack].getDeckAmount())
					indexOfShipWithMaxDack = i;
			}
		}

		//filling the array with recommended coordinates for the fastest destroying of the biggest ship
		int  templateArray[10][10];
		int deckAmount = this->playerMap->getShips()[indexOfShipWithMaxDack].getDeckAmount();
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (j == deckAmount - 1 - i + (i / deckAmount + j / deckAmount) * deckAmount) //int square = i / deckAmount + j / deckAmount;
					templateArray[i][j] = 1;
				else
					templateArray[i][j] = 0;
				//std::cout << templateArray[i][j] << " ";
			}
			//std::cout << std::endl;
		}

		//merging two arrays: the first one is templateArray which contains recommended coordinates for the fastest destroying of the biggest ship. The second one is map which contains explored field of map
		std::vector<sf::Vector2i> coordForAttack;
		for (int i = 0; i < this->playerMap->getSizeI() * this->playerMap->getSizeJ(); i++)
		{
			int coorj = i % 10;
			int coori = (i - coorj) / 10;
			int mapValue = this->playerMap->getMapValue(coori, coorj);

			if (templateArray[coori][coorj] == 1 && (mapValue == 0 || mapValue == 1))
				coordForAttack.emplace_back(coori, coorj);
		}

		if (!coordForAttack.empty())
		{
			int i = rand() % coordForAttack.size();
			botAttack(coordForAttack[i].x, coordForAttack[i].y);
		}
	}
	//the ship has been damaged, we aproximatly know coordinates where could be a deck, we should strike next to it. 
	//In general case, we have four direction for continue attack. Now we should determine direction of ship.
	else if (this->damagedDecks.size() == 1)
	{
		//std::cout << " 111 " << std::endl;
		
		if (checkField(damagedDecks[0].i - 1, damagedDecks[0].j))
			botAttack(damagedDecks[0].i - 1, damagedDecks[0].j);

		else if (checkField(damagedDecks[0].i + 1, damagedDecks[0].j))
			botAttack(damagedDecks[0].i + 1, damagedDecks[0].j);

		else if (checkField(damagedDecks[0].i, damagedDecks[0].j - 1))
			botAttack(damagedDecks[0].i, damagedDecks[0].j - 1);

		else if (checkField(damagedDecks[0].i, damagedDecks[0].j + 1))
			botAttack(damagedDecks[0].i, damagedDecks[0].j + 1);

		else 
			MessageBox(0, (LPCWSTR)L"Bot attack1", (LPCWSTR)L"Error message", 0);

	}
	//we've determined direction of the ship. Now we should finish it off.
	else
	{
		//std::cout << " 222 " << std::endl;
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

				else
					MessageBox(0, (LPCWSTR)L"Bot attack2", (LPCWSTR)L"Error message", 0);
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

				else
					MessageBox(0, (LPCWSTR)L"Bot attack3", (LPCWSTR)L"Error message", 0);
			}
		}
		else
			MessageBox(0, (LPCWSTR)L"Bot attack4", (LPCWSTR)L"Error message", 0);
	}
}

void GameState::update(sf::RenderWindow* targetWindow)
{
	this->mouseUpdatePosition(targetWindow);

	for (auto it : this->buttons)
		it.second->update(this->mousePosWindowf);

	enemyMap.updateMap(this->mousePosWindowf, 1);
	playerMap->updateMap(this->mousePosWindowf);

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
				
				//this->enemyMap.getMapValue(); 
				//std::cout << std::endl;
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
			if (clock.getElapsedTime().asSeconds() > 0.3)
			{
				ArtificInt();
				this->clock.restart();
			}
		}
		else this->textInfo.setString("Your move");
	}
	else if (enemyMap.getCurrentShipsAmount() <= 0 && this->winFlag == 0)
	{
		this->textInfo.setString("YOU WIN!");

		this->soundWin.play();
		this->winFlag = 1;
	}
	else if(this->winFlag == 0)
	{
		this->textInfo.setString("YOU LOSE!");
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
