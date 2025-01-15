#pragma once
#include "raylib.h"
#include "Resources.h"
#include "game.h"

struct Projectile
{
public:
	
	Vector2 position = { 0,0 };
	Vector2 lineStart = { 0, 0 };
	Vector2 lineEnd = { 0, 0 };
	int speed = 15;
	bool active = true;
	EntityType type; 

	std::vector<Projectile> Projectiles;
	

	void Update();

	void Render(const GameTexture& texture) const;
};