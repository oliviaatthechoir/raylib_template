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

	Wall() {}; 

	 Wall(Vector2 initialPosition = {0, 0}, Vector2 initialSize = {50, 50}, Color initialColor = WHITE)
        : position(initialPosition), size(initialSize), color(initialColor) 
    {}

	void Initialize(); 
	void Update();
	void Render(const GameTexture& texture) const;

	~Wall() = default; 

};
