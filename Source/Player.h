#pragma once
#include "raylib.h"
#include <vector>

class Player
{
public:

	float x_pos = 0;
	float speed = 7;
	float player_base_height = 70.0f;
	float radius = 50;
	int lives = 3;
	int direction = 0;
	int activeTexture = 0;
	float timer = 0;

	Player() = default; 

	 Player(float xPos, int lives = 3, float baseHeight = 70.0f, float radius = 50.0f, float speed = 7.0f) 
	: x_pos(xPos), speed(speed), player_base_height(baseHeight), radius(radius), lives(lives) {
		
	}; 

	
	void Render(Texture2D texture) const;
	void Update();

	Vector2 playerPos;
	Vector2 cornerPos;
	float offset;

	~Player() = default; 

};
