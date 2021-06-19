#include "Legend.h"

Legend::Legend()
{
	//init font
	if (!this->font.loadFromFile("Fonts\\font.ttf"))	std::cout << "Font error" << std::endl; //should be refined

	//init legend
	textLegend.setFont(font);
	textLegend.setCharacterSize(21);
	textLegend.setPosition(sf::Vector2f(775, 150));

	this->textLegendHeader.setFont(font);
	this->textLegendHeader.setCharacterSize(21);
	this->textLegendHeader.setPosition(sf::Vector2f(730, 105));

	this->unexploredField.setFillColor(sf::Color::Blue);
	this->unexploredField.setPosition(738, 150);
	this->unexploredField.setSize(sf::Vector2f(27.f, 27.f));

	this->emptyField.setFillColor(sf::Color::Green);
	this->emptyField.setPosition(738, 200);
	this->emptyField.setSize(sf::Vector2f(27.f, 27.f));

	this->deckOfShip.setFillColor(sf::Color::White);
	this->deckOfShip.setPosition(738, 250);
	this->deckOfShip.setSize(sf::Vector2f(27.f, 27.f));

	this->destrDeck.setFillColor(sf::Color::Red);
	this->destrDeck.setPosition(738, 300);
	this->destrDeck.setSize(sf::Vector2f(27.f, 27.f));

	this->bound.setFillColor(sf::Color(5, 5, 5, 0));
	this->bound.setOutlineColor(sf::Color::White);
	this->bound.setOutlineThickness(3);
	this->bound.setPosition(730, 137);
	this->bound.setSize(sf::Vector2f(325.f, 200.f));

	std::stringstream ss;
	ss.str("");
	ss << " - unexplored map field\n\n";
	ss << " - there is no ship in this area\n\n";
	ss << " - deck of ship\n\n";
	ss << " - destroyed deck of ship";

	this->textLegend.setString(ss.str());

	ss.str("");
	ss << " Legend ";
	textLegendHeader.setString(ss.str());
}

Legend::~Legend()
{
}

void Legend::update(sf::RenderWindow* targetWindow)
{
}

void Legend::render(sf::RenderWindow* targetWindow)
{
	targetWindow->draw(this->unexploredField);
	targetWindow->draw(this->emptyField);
	targetWindow->draw(this->deckOfShip);
	targetWindow->draw(this->destrDeck);
	targetWindow->draw(this->bound);
	targetWindow->draw(this->textLegendHeader);
	targetWindow->draw(this->textLegend);
}
