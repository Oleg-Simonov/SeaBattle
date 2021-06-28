#include "Legend.h"

Legend::Legend(int x, int y)
{
	//init font
	if (!this->font.loadFromFile("Fonts\\font.ttf"))	std::cout << "Font error" << std::endl; //should be refined

	//init legend
	textLegend.setFont(font);
	textLegend.setCharacterSize(17);
	textLegend.setPosition(sf::Vector2f(x + 30, y + 15));

	this->textLegendHeader.setFont(font);
	this->textLegendHeader.setCharacterSize(21);
	this->textLegendHeader.setPosition(sf::Vector2f(x + 15, y - 35));

	this->unexploredField.setFillColor(sf::Color::Blue);
	this->unexploredField.setPosition(x + 10, y + 19);
	this->unexploredField.setSize(sf::Vector2f(17.f, 17.f));

	this->emptyField.setFillColor(sf::Color::Green);
	this->emptyField.setPosition(x + 10, y + 19 *2);
	this->emptyField.setSize(sf::Vector2f(17.f, 17.f));

	this->deckOfShip.setFillColor(sf::Color::White);
	this->deckOfShip.setPosition(x + 10, y + 19 * 3);
	this->deckOfShip.setSize(sf::Vector2f(17.f, 17.f));

	this->destrDeck.setFillColor(sf::Color::Red);
	this->destrDeck.setPosition(x + 10, y + 19 * 4);
	this->destrDeck.setSize(sf::Vector2f(17.f, 17.f));

	this->bound.setFillColor(sf::Color(51, 51, 51, 150));
	this->bound.setOutlineColor(sf::Color::White);
	this->bound.setOutlineThickness(3);
	this->bound.setPosition(x, y); // 730, 137);
	this->bound.setSize(sf::Vector2f(250.f, 110.f));

	std::stringstream ss;
	ss.str("");
	ss << " - unexplored map field\n";
	ss << " - there is no ship in this area\n";
	ss << " - deck of ship\n";
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
	targetWindow->draw(this->bound);
	targetWindow->draw(this->unexploredField);
	targetWindow->draw(this->emptyField);
	targetWindow->draw(this->deckOfShip);
	targetWindow->draw(this->destrDeck);
	targetWindow->draw(this->textLegendHeader);
	targetWindow->draw(this->textLegend);
}
