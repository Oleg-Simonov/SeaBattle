#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
//#include "Map.h"

	class OutMapShip
	{
	public:
		float windowCoorX, windowCoorY;
		int deckAmount;
		bool grab, direction;
		int color;
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

		void update(sf::RenderWindow* window, int prohibitedZoneValue);

		void render(sf::RenderWindow* window);
	};


