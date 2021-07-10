#include "Game.h"

Game::Game()
{
	this->currentState = 0;

	//init window
	this->videoMode.width = 1200;
	this->videoMode.height = 630;
	this->window = new sf::RenderWindow(videoMode, "SeaBattle v0.1", sf::Style::Close);
	this->window->setFramerateLimit(60);
	this->window->setKeyRepeatEnabled(false);

	this->states.push_back(new PlacingState(&this->states));
}

Game::~Game()
{
	delete this->window;
	this->window = nullptr;

	while (!this->states.empty())
	{
		delete this->states.back();
		this->states.back() = nullptr;
		this->states.pop_back();
	}
	//std::cout << "GAME_________DESTR" << std::endl;
}

bool Game::getWindowStatus() const
{
	return this->window->isOpen();
}

void Game::update()
{
	//update current state
	if (!this->states.empty())
	{
		this->states.back()->update(this->window);

		if (this->states.back()->getEndState() == 1) //restart
		{
			while (!this->states.empty())
			{
				delete this->states.back();
				this->states.back() = nullptr;
				this->states.pop_back();
			}

			this->states.push_back(new PlacingState(&this->states));
		}

		if (this->states.back()->getEndState() == -1) //quit
		{
			while (!this->states.empty())
			{
				delete this->states.back();
				this->states.back() = nullptr;
				this->states.pop_back();
			}
		}
	}
	else
		this->window->close();
}

void Game::render()
{
	this->window->clear();

	//render current state
	if (!this->states.empty())
		this->states.back()->render(this->window);
	this->window->display();
}




