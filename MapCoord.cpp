#include "MapCoord.h"

MapCoord::MapCoord()
{
	//std::cout << "cor const1" << std::endl;
	this->i = -1;
	this->j = -1;
}

MapCoord::MapCoord(int i, int j)
{
	//std::cout << "cor const2" << std::endl;
	this->i = i;
	this->j = j;
}

MapCoord::MapCoord(const MapCoord& otherMapCoord)
{
	//std::cout << "cor const Copy" << std::endl;
	this->i = otherMapCoord.i;
	this->j = otherMapCoord.j;
}

MapCoord::~MapCoord()
{
	//std::cout << "cor destr" << std::endl;
}
