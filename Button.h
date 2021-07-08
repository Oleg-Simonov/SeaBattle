#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum button_status { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

class Button
{
private:
	short unsigned buttonState;

	bool visible;
	bool flagHover;

	sf::SoundBuffer soundBufferHover;
	sf::Sound soundHover;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x, float y, float width, float height, 
		sf::Font* font, std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, bool visible = 1);
	~Button();

	const bool isPressed() const;
	void setVisible(bool value);

	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget* target);
};

