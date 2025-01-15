#include "Alien.h"

Alien::Alien() : position({ 0,0 }), radius(30.0f), active(true), moveRight(true), speed(2) {}; 

void Alien::Initialize(Vector2 startPosition, int movementSpeed) {
	position = startPosition; 
	speed = movementSpeed; 
	active = true; 
	moveRight = true; 
	
}

void Alien::Update() {
	if (moveRight)
	{
		position.x += (float)speed;

		if (position.x >= (float)GetScreenWidth())
		{
			moveRight = false;
			position.y += 50;
		}
	}
	else
	{
		position.x -= (float)speed;

		if (position.x <= 0)
		{
			moveRight = true;
			position.y += 50;
		}
	}
}

void Alien::Render(const GameTexture& texture) const {
	DrawTexture(texture.texture, (int)position.x, (int)position.y, WHITE); 
}