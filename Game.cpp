#include "Game.h"

Game::Game()
{
	//init window
	this->videoMode.width = 1100;
	this->videoMode.height = 700;
	this->window = new sf::RenderWindow(videoMode, "SeaBattle");
	this->window->setFramerateLimit(60);

	this->states.emplace(new PlacingState(&this->states));
	//this->states.emplace(new MainMenuState(&this->states));
	//this->states.emplace(new GameState(&this->states));
}

Game::~Game()
{
	delete this->window;
	this->window = nullptr;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

bool Game::getWindowStatus() const
{
	return this->window->isOpen();
}

void Game::update()
{

	//poll events----------------------------------------------------
	while (this->window->pollEvent(sfEvent))
	{
		if (this->sfEvent.type == sf::Event::EventType::Closed)
			this->window->close();
	}

	//update current state
	if (!this->states.empty())
	{
		this->states.top()->update(this->window);
		
		
		if (this->states.top()->getEndState() == 1)
		{
			delete this->states.top();
			this->states.pop();
		}

		else if (this->states.top()->getEndState() == 2)
		{
			while (!this->states.empty())
			{
				delete this->states.top();
				this->states.pop();
			}
			this->states.emplace(new PlacingState(&this->states));
		}

		else if (this->states.top()->getEndState() == 3)
		{
			while (!this->states.empty())
			{
				delete this->states.top();
				this->states.pop();
			}
		}
	}
	else this->window->close();
	
}

void Game::render()
{
	this->window->clear();

	//render current state
	if (!this->states.empty())
		this->states.top()->render(this->window);
	this->window->display();
}




