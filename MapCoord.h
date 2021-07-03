#pragma once
#include <iostream>

class MapCoord
{
public:
	int i, j;

	MapCoord();
	MapCoord(int i, int j);
	MapCoord(const MapCoord& otherMapCoord);
	~MapCoord();
};

