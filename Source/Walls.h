#pragma once
#include "raylib.h"
#include "Resources.h"

struct Wall
{
public:
	Vector2 position;
	Rectangle rec;
	bool active;
	Color color;
	int health = 50;
	int radius = 60;

	int wallCount = 5;
	std::vector<Wall> Walls;


	void Initialize(); 
	void Update();
	void Render(const GameTexture& texture) const;

};