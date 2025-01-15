#include "Walls.h"

void Wall::Initialize() {
	// creating walls 
	auto window_width = (float)GetScreenWidth();
	auto window_height = (float)GetScreenHeight();
	float wall_distance = window_width / (float)(wallCount + 1);
	for (int i = 0; i < wallCount; i++)
	{
		Wall newWalls;
		newWalls.position.y = window_height - 250;
		newWalls.position.x = wall_distance * (float)(i + 1);

		Walls.push_back(newWalls);

	}
}

void Wall::Update() {
	for (auto& wall : Walls)
	{
		if (CheckCollision(wall.position, (float)wall.radius, projectile.lineStart, projectile.lineEnd))
		{
			// Kill!
			std::cout << "Hit! \n";
			// Set them as inactive, will be killed later
			projectile.active = false;
			wall.health -= 1;
		}
	}

	if (health < 1)
	{
		active = false;
	}
}

void Wall::Render(const GameTexture& texture) const{
	DrawTexture(texture.texture, (int)position.x - 100, (int)position.y - 100, WHITE);
	DrawText(TextFormat("%d", health), (int)position.x - 21, (int)position.y + 10, 40, RED);
}

