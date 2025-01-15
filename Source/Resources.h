#pragma once
#include "raylib.h"
#include "vector"
#include "Texture.h"


class Resources 
{
public: 
	Texture AlienTexture;
	Texture WallTexture; 
	Texture ShipTexture; 

	Resources() : AlienTexture("Assets/Alien.png"),
		WallTexture("Assets/Barrier.png"), ShipTexture("Assets/Ship1.png") { }


};

