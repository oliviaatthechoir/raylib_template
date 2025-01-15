#pragma once
#ifndef RESOURCES_H
#define RESOURCES_H



#include <string>
#include <array>
#include "raylib.h"
#include "vector"

struct GameTexture {
	Texture2D texture; 
	explicit GameTexture(std::string_view path) {
		texture = LoadTexture(path.data()); 
	}


	~GameTexture() {
		UnloadTexture(texture); 
	}

	


	
};


struct Resources
{
	std::array<GameTexture, 3> shipTextures = { GameTexture("./Assets/Ship1.png"), GameTexture("./Assets/Ship2.png"), GameTexture("./Assets/Ship3.png") };
	GameTexture alienTexture = GameTexture("./Assets/Alien.png");
	GameTexture barrierTexture = GameTexture("./Assets/Barrier.png");
	GameTexture laserTexture = GameTexture("./Assets/Laser.png");
};


#endif // !RESOURCES_h




