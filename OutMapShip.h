#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

	class OutMapShip
	{
	public:
		float windowCoorX, windowCoorY;
		int deckAmount;
		bool grab, direction;
		sf::RectangleShape shape;

		OutMapShip(float windowCoorX, float windowCoorY, int deckAmount);
		~OutMapShip();

		float getWindowCoorX() const;
		float getWindowCoorY() const;
		int getDeckAmount() const;
		bool getGrab() const;
		bool getDirection() const;

		void setWindowCoorX(float windowCoorX);
		void setWindowCoorY(float windowCoorY);
		void setDeckAmount(int deckAmount);
		void setGrab(bool grab);
		void setDirection();

		void update(sf::RenderWindow* window);

		void render(sf::RenderWindow* window);
	};


