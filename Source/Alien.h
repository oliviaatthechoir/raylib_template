#pragma once
#include "raylib.h"
#include "Resources.h"
#include <vector>


struct Alien
{
public:

	Color color = WHITE;
	Vector2 position = { 0, 0 };
	int x = 0;
	int y = 0;
	float radius = 30;
	bool active = true;
	bool moveRight = true;

	int speed = 2;

	
	Vector2 alienPos;
	std::vector<Alien> Aliens;
 
	void Initialize(Vector2 startPosition, int movementSpeed); 
	void Update();
	void Render(const GameTexture& texture) const;
};