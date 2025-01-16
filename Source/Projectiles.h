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

	Projectile() = default; 


	 Projectile(Vector2 initialPosition = {0, 0}, int initialSpeed = 15, EntityType entityType = EntityType::Projectile)
    : position(initialPosition), speed(initialSpeed), active(true), type(entityType) {}


	std::vector<Projectile> projectile;
	

	void Update();

	void Render(const GameTexture& texture) const;

	~Projectile() = default; 
};
