#include "Projectiles.h"

void Projectile::Update() {
	position.y -= (float)speed;

	// UPDATE LINE POSITION
	lineStart.y = position.y - 15;
	lineEnd.y = position.y + 15;

	lineStart.x = position.x;
	lineEnd.x = position.x;

	if (position.y < 0 || position.y > 1500)
	{
		active = false;
	}
}

void Projectile::Render(const GameTexture& texture) const {
	DrawTexture(texture.texture, (int)position.x - 25, (int)position.y - 25, WHITE); 
}