#include "Button.h"

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, bool visible)
{
	this->buttonState = BTN_IDLE;
	this->flagHover = false;

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
	this->visible = visible;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(this->idleColor);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(17);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	//sound init
	if (!soundBufferHover.loadFromFile("Resources\\Sounds\\ButtonHover.wav")) std::cout << "sound error" << std::endl; //should be refined
	this->soundHover.setBuffer(soundBufferHover);
	this->soundHover.setVolume(35.f);
}

Button::~Button()
{
	//std::cout << "BUTTON_____________DESTR" << std::endl;
}

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}

void Button::setVisible(bool value)
{
	this->visible = value;
}

void Button::update(const sf::Vector2f& mousePos)
{
	if (visible)
	{
		this->buttonState = BTN_IDLE;
		if (this->shape.getGlobalBounds().contains(mousePos))
		{
			this->buttonState = BTN_HOVER;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->buttonState = BTN_ACTIVE;
			}
		}

		switch (this->buttonState)
		{
		case BTN_IDLE:
			this->shape.setFillColor(this->idleColor);
			flagHover = 0;
			break;

		case BTN_HOVER:
			if (flagHover == 0)
			{
				this->soundHover.play();
				flagHover = 1;
			}

			this->shape.setFillColor(this->hoverColor);
			break;

		case BTN_ACTIVE:
			this->shape.setFillColor(this->activeColor);
			break;

		default:
			this->shape.setFillColor(sf::Color::Red);
			break;
		}
	}
}

void Button::render(sf::RenderTarget* target)
{
	if (visible)
	{
		target->draw(this->shape);
		target->draw(this->text);
	}
}
