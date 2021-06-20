#include "OutMapShip.h"

OutMapShip::OutMapShip(float windowCoorX, float windowCoorY, int deckAmount)
{
    this->windowCoorX = windowCoorX;
    this->windowCoorY = windowCoorY;
    this->deckAmount = deckAmount;
    this->grab = false;
    this->direction = false;

    this->shape.setPosition(this->windowCoorX, this->windowCoorY);
    this->shape.setSize(sf::Vector2f(27.f, 27.f * this->deckAmount + this->deckAmount));
    this->shape.setFillColor(sf::Color::White);
    this->shape.setOutlineThickness(1.f);
    this->shape.setOutlineColor(sf::Color::Black);
}

OutMapShip::~OutMapShip()
{
}

float OutMapShip::getWindowCoorX() const
{
    return this->windowCoorX;
}

float OutMapShip::getWindowCoorY() const
{
    return windowCoorY;
}

int OutMapShip::getDeckAmount() const
{
    return this->deckAmount;
}

bool OutMapShip::getGrab() const
{
    return this->grab;
}

bool OutMapShip::getDirection() const
{
    return this->direction;
}

void OutMapShip::setGrab(bool grab)
{
        this->grab = grab;
}

void OutMapShip::setDirection()
{
    if (this->direction == false)
        this->direction = true;
    else
        this->direction = false;

}

void OutMapShip::update(sf::RenderWindow* window, int prohibitedZoneValue)
{
    if (grab)
    {
            this->shape.setPosition((float)sf::Mouse::getPosition(*window).x - 15, (float)sf::Mouse::getPosition(*window).y - 15);

            if (direction)   this->shape.setSize(sf::Vector2f(27.f * this->deckAmount + this->deckAmount, 27.f));

            else   this->shape.setSize(sf::Vector2f(27.f, 27.f * this->deckAmount + this->deckAmount));
    }
    else
    {
        this->shape.setPosition(this->windowCoorX, this->windowCoorY);
        this->shape.setSize(sf::Vector2f(27.f, 27.f * this->deckAmount + this->deckAmount));
        this->shape.setFillColor(sf::Color::White);
        this->shape.setOutlineThickness(1.f);
        this->shape.setOutlineColor(sf::Color::Black);
    }
 
    if (this->shape.getGlobalBounds().contains((float)sf::Mouse::getPosition(*window).x, (float)sf::Mouse::getPosition(*window).y))
    {
        if (prohibitedZoneValue == 0) this->shape.setFillColor(sf::Color::Green);
        else if (prohibitedZoneValue == -1) this->shape.setFillColor(sf::Color::Cyan);
        else this->shape.setFillColor(sf::Color::Red);
    }
}

void OutMapShip::render(sf::RenderWindow* window)
{
    window->draw(this->shape);
}


