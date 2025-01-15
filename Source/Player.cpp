#include "Player.h"
#include <algorithm>
#include <iostream>

void Player::Initialize()
{
	auto window_width = (float)GetScreenWidth();
	x_pos = window_width / 2;
	std::cout << "Find Player -X:" << GetScreenWidth() / 2 << "Find Player -Y" << (float)GetScreenHeight() - player_base_height << std::endl;
}


void Player::Update()
{

	//Movement
	direction = 0;
	if (IsKeyDown(KEY_LEFT))
	{
		direction--;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		direction++;
	}

	x_pos += speed * (float)direction;

	if (x_pos < 0 + radius)
	{
		x_pos = 0 + radius;
	}
	else if (x_pos > (float)GetScreenWidth() - radius)
	{
		x_pos = (float)GetScreenWidth() - radius;
	}


	//Determine frame for animation
	timer += GetFrameTime();

	if (timer > 0.4 && activeTexture == 2)
	{
		activeTexture = 0;
		timer = 0;
	}
	else if (timer > 0.4)
	{
		activeTexture++;
		timer = 0;
	}
}

void Player::Render(Texture2D texture) const {
	auto window_height = (float)GetScreenHeight(); 
	DrawTexture(texture, (int)x_pos - (int)radius, (int)player_base_height - (int)radius, WHITE); 
}