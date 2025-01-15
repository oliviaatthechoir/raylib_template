#include "game.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <algorithm> 

//TODO: this should only be game 

// MATH FUNCTIONS
float lineLength(Vector2 A, Vector2 B) //Uses pythagoras to calculate the length of a line
{
	float length = sqrtf(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));

	return length;
}

bool pointInCircle(Vector2 circlePos, float radius, Vector2 point) // Uses pythagoras to calculate if a point is within a circle or not
{
	float distanceToCentre = lineLength(circlePos, point);

	if (distanceToCentre < radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Game::Start()
{
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


	//creating player
	Player newPlayer;
	player = newPlayer;
	player.Initialize();

	
	

	//creating background
	Background newBackground;
	newBackground.Initialize(600);
	background = newBackground;

	//reset score
	score = 0;

	gameState = State::GAMEPLAY;

}

void Game::End()
{
	//SAVE SCORE AND UPDATE SCOREBOARD
	Projectiles.clear();
	Walls.clear();
	//Aliens.clear();
	newHighScore = CheckNewHighScore();
	gameState = State::ENDSCREEN;
}

void Game::Continue()
{
	SaveLeaderboard();
	gameState = State::STARTSCREEN;
}

void Game::Launch() const {

}

void Game::Update()
{
	switch (gameState)
	{
	case State::STARTSCREEN:
		//Code 
		if (IsKeyReleased(KEY_SPACE))
		{
			Start();


		}

		break;
	case State::GAMEPLAY:
		//Code
		if (IsKeyReleased(KEY_Q))
		{
			End();
		}

		//Update Player
		player.Update();
		
		//Update Aliens and Check if they are past player
		for (auto& alien : Aliens)
		{
			alien.Update(); 

			if (alien.position.y > GetScreenHeight() - player.player_base_height)
			{
				End();
			}
		}

		//End game if player dies
		if (player.lives < 1)
		{
			End();
		}

		//Spawn new aliens if aliens run out
		if (Aliens.size() < 1)
		{
			SpawnAliens();
		}


		// Update background with offset
		playerPos = { player.x_pos, player.player_base_height };
		cornerPos = { 0, player.player_base_height };
		offset = lineLength(playerPos, cornerPos) * -1;
		background.Update(offset / 15);


		//UPDATE PROJECTILE
		for (auto& projectile : Projectiles)
		{
			projectile.Update(); 
		}
		//UPDATE PROJECTILE
		for (auto& wall : Walls)
		{
			wall.Update(); 
		}

		//CHECK ALL COLLISONS HERE
		for (auto& projectile : Projectiles)
		{
			if (projectile.type == EntityType::PLAYER_PROJECTILE)
			{
				for (auto& alien : Aliens)
				{
					if (CheckCollision(alien.position, alien.radius, projectile.lineStart, projectile.lineEnd))
					{
						// Kill!
						std::cout << "Hit! \n";
						// Set them as inactive, will be killed later
						projectile.active = false;
						alien.active = false;
						score += 100;
					}
				}
			}

			//ENEMY PROJECTILES HERE
			for (auto& projectile : Projectiles)
			{
				if (projectile.type == EntityType::ENEMY_PROJECTILE)
				{
					if (CheckCollision({player.x_pos, GetScreenHeight() - player.player_base_height }, player.radius, projectile.lineStart, projectile.lineEnd))
					{
						std::cout << "dead!\n"; 
						projectile.active = false; 
						player.lives -= 1; 
					}
				}
			}


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
		}

		//MAKE PROJECTILE
		if (IsKeyPressed(KEY_SPACE))
		{
			auto window_height = (float)GetScreenHeight();
			Projectile newProjectile;
			newProjectile.position.x = player.x_pos;
			newProjectile.position.y = window_height - 130;
			newProjectile.type = EntityType::PLAYER_PROJECTILE;
			Projectiles.push_back(newProjectile);
		}

		//Aliens Shooting
		shootTimer += 1;
		if (shootTimer > 59) //once per second
		{
			int randomAlienIndex = 0;

			if (Aliens.size() > 1)
			{
				randomAlienIndex = rand() % Aliens.size();
			}

			Projectile newProjectile;
			newProjectile.position = Aliens[randomAlienIndex].position;
			newProjectile.position.y += 40;
			newProjectile.speed = -15;
			newProjectile.type = EntityType::ENEMY_PROJECTILE;
			Projectiles.push_back(newProjectile);
			shootTimer = 0;
		}

		// REMOVE INACTIVE/DEAD ENITITIES
		std::erase_if(Projectiles, [](const auto& projectile) {
			return !projectile.active; 
		});

		std::erase_if(Aliens, [](const auto& alien) {
			return !alien.active; 
		}); 

		std::erase_if(Walls, [](const auto& wall) {
			return !wall.active; 
		}); 

			

	break;
	case State::ENDSCREEN:
		
		if (!newHighScore && IsKeyPressed(KEY_ENTER))
		{
			
			Continue();  
			return;
			
		}

		
		if (newHighScore)
		{
			
			if (CheckCollisionPointRec(GetMousePosition(), textBox))
				mouseOnText = true;
			else
				mouseOnText = false;

			
			if (mouseOnText)
			{
				
				SetMouseCursor(MOUSE_CURSOR_IBEAM);

				
				int key = GetCharPressed();

				
				while (key > 0)
				{
					
					if ((key >= 32) && (key <= 125) && (name.size() < 9))
					{
						name += static_cast<char>(key); 
					}

					key = GetCharPressed(); 
				}

				
				if (IsKeyPressed(KEY_BACKSPACE) && !name.empty())
				{
					name.pop_back();
				}
			}
			else
			{
				SetMouseCursor(MOUSE_CURSOR_DEFAULT);
			}

			
			if (mouseOnText)
			{
				framesCounter++;
			}
			else
			{
				framesCounter = 0;
			}

			
			if (IsKeyPressed(KEY_ENTER) && !name.empty())
			{
				InsertNewHighScore(name);  
				newHighScore = false;     
			}
		}

		break;

	default:
		
		break;
	}
}

void Game::HandleStartScreen() {
	if (IsKeyReleased(KEY_SPACE)) {
		Start();
	}
}

void Game::HandleGamePlay() {
	if (IsKeyReleased(KEY_Q)) {
		End();
		return;
	}
}



void Game::Render()
{
	switch (gameState)
	{
	case State::STARTSCREEN:
		RenderStartScreen(); 

		break;
	case State::GAMEPLAY:
		RenderGamePlay(); 

		break;
	case State::ENDSCREEN:
		RenderEndScreen(); 

		break;
	default:
		
		break;
	}
}

void Game::RenderStartScreen() const {
	
	DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);
	DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
}

void Game::RenderGamePlay() {
	background.Render(); 

	DrawText(TextFormat("Score: %i", score), 50, 20, 40, YELLOW);
	DrawText(TextFormat("Lives: %i", player.lives), 50, 70, 40, YELLOW);

	player.Render(resources.shipTextures[player.activeTexture].texture);

	for (const auto& projectile : Projectiles)
	{
		projectile.Render(resources.laserTexture);
	}

	for (const auto& wall : Walls)
	{
		wall.Render(resources.barrierTexture);
	}

	for (const auto& alien : Aliens)
	{
		alien.Render(resources.alienTexture.texture);
	}
}

void Game::RenderEndScreen() {
	if (newHighScore) {
		RenderHighScoreInput();
	}
	else
	{
		RenderLeaderboard(); 
	}
}

void Game::RenderHighScoreInput() const{
	DrawText("NEW HIGHSCORE!", 600, 300, 60, YELLOW);
	DrawText("PLACE MOUSE OVER INPUT BOX!", 600, 400, 20, YELLOW);

	DrawRectangleRec(textBox, LIGHTGRAY);

	Color borderColor = mouseOnText ? RED : DARKGRAY;
	DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, borderColor);

	if (name.empty())
	{
		DrawText(" ", (int)textBox.x + 5, (int)textBox.y + 8, 40, GRAY);
	}
	else
	{
		DrawText(name.c_str(), (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
	}

	DrawText(TextFormat("INPUT CHARS: %i/9", name.size()), 600, 600, 20, YELLOW);

	if (mouseOnText)
	{
		RenderCursorBlink();
	}

	if (!name.empty())
	{
		DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
	}

}

void Game::RenderCursorBlink() const {
	if (letterCount < 9 && ((framesCounter / 20) % 2) == 0)
	{
		int textWidth = MeasureText(name.c_str(), 40);
		DrawText("_", (int)textBox.x + 8 + textWidth, (int)textBox.y + 12, 40, MAROON);
	}
	else if (letterCount >= 9)
	{
		DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
	}
}

void Game::RenderLeaderboard() {
	DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);
	DrawText("LEADERBOARD", 50, 100, 40, YELLOW);

	for (int i = 0; i < Leaderboard.size(); i++)
	{
		DrawText(Leaderboard[i].name.c_str(), 50, 140 + (i * 40), 40, YELLOW);
		DrawText(TextFormat("%i", Leaderboard[i].score), 350, 140 + (i * 40), 40, YELLOW);
	}
}



bool Game::CheckNewHighScore()
{
	if (score > Leaderboard[4].score)
	{
		return true;
	}

	return false;
}

void Game::InsertNewHighScore(const std::string_view& name)
{
	PlayerData newData;
	newData.name = name;
	newData.score = score;

	for (int i = 0; i < Leaderboard.size(); i++)
	{
		if (newData.score > Leaderboard[i].score)
		{

			Leaderboard.insert(Leaderboard.begin() + i, newData);

			Leaderboard.pop_back();

			break; 

		}
	}
	SaveLeaderboard(); 
}



void Game::SaveLeaderboard() const
{
	// SAVE LEADERBOARD AS ARRAY

	// OPEN FILE
	std::fstream file;

	file.open("Leaderboard", std::ios::out | std::ios::trunc);

	if (!file)
	{
		std::cout << "file not found \n";
		return; 
	}
	else
	{
		std::cout << "file found \n";
	}

	for (const auto& player : Leaderboard) {
		file << player.name << " " << player.score << '\n'; 
	}

	file.close(); 
	// CLEAR FILE

	// WRITE ARRAY DATA INTO FILE

	// CLOSE FILE
}


bool Game::CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineStart, Vector2 lineEnd) const
{
	// our objective is to calculate the distance between the closest point on the line to the centre of the circle, 
	// and determine if it is shorter than the radius.

	// check if either edge of line is within circle
	if (pointInCircle(circlePos, circleRadius, lineStart) || pointInCircle(circlePos, circleRadius, lineEnd))
	{
		return true;
	}

	// simplify variables
	Vector2 A = lineStart;
	Vector2 B = lineEnd;
	Vector2 C = circlePos;

	// calculate the length of the line
	float length = lineLength(A, B);
	
	// calculate the dot product
	float dotP = (((C.x - A.x) * (B.x - A.x)) + ((C.y - A.y) * (B.y - A.y))) / pow(length, 2);

	// use dot product to find closest point
	float closestX = A.x + (dotP * (B.x - A.x));
	float closestY = A.y + (dotP * (B.y - A.y));

	//find out if coordinates are on the line.
	// we do this by comparing the distance of the dot to the edges, with two vectors
	// if the distance of the vectors combined is the same as the length the point is on the line

	//since we are using floating points, we will allow the distance to be slightly innaccurate to create a smoother collision
	float buffer = 0.1;

	float closeToStart = lineLength(A, { closestX, closestY }); //closestX + Y compared to line Start
	float closeToEnd = lineLength(B, { closestX, closestY });	//closestX + Y compared to line End

	float closestLength = closeToStart + closeToEnd;

	if (closestLength == length + buffer || closestLength == length - buffer)
	{
		//Point is on the line!

		//Compare length between closest point and circle centre with circle radius

		float closeToCentre = lineLength(A, { closestX, closestY }); //closestX + Y compared to circle centre

		if (closeToCentre < circleRadius)
		{
			//Line is colliding with circle!
			return true;
		}
		else
		{
			//Line is not colliding
			return false;
		}
	}
	else
	{
		// Point is not on the line, line is not colliding
		return false;
	}

}






void Projectile::Update()
{
	position.y -= (float)speed;

	// UPDATE LINE POSITION
	lineStart.y = position.y - 15;
	lineEnd.y   = position.y + 15;

	lineStart.x = position.x;
	lineEnd.x   = position.x;

	if (position.y < 0 || position.y > 1500)
	{
		active = false;
	}
}

void Projectile::Render(GameTexture& texture) const 
{
	
	DrawTexturePro(texture.texture,
		{
			0,
			0,
			176,
			176,
		},
		{
			position.x,
			position.y,
			50,
			50,
		}, { 25 , 25 },
		0,
		WHITE);
}

void Wall::Render(GameTexture& texture) const
{
	DrawTexturePro(texture.texture,
		{
			0,
			0,
			704,
			704,
		},
		{
			position.x,
			position.y,
			200,
			200,
		}, { 100 , 100 },
		0,
		WHITE);


	DrawText(TextFormat("%i", health), (int)position.x-21, (int)position.y+10, 40, RED);
	
}

void Wall::Update() 
{
	if (health < 1)
	{
		active = false;
	}
}

void Alien::Update() 
{
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

void Alien::Render(Texture2D texture) const 
{
	
	DrawTexturePro(texture,
		{
			0,
			0,
			352,
			352,
		},
		{
			position.x,
			position.y,
			100,
			100,
		}, {50 , 50},
		0,
		WHITE);
}


//BACKGROUND
void Star::Update(float starOffset)
{
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;

}

void Star::Render() const 
{
	DrawCircle((int)position.x, (int)position.y, size, color);
}


void Background::Initialize(int starAmount)
{
	for (int i = 0; i < starAmount; i++)
	{
		Star newStar;

		newStar.initPosition.x = (float)GetRandomValue(-150, GetScreenWidth() + 150);
		newStar.initPosition.y = (float)GetRandomValue(0, GetScreenHeight());
		
		//random color?
		newStar.color = SKYBLUE;

		newStar.size = (float)GetRandomValue(1, 4) / static_cast<float>(2);

		Stars.push_back(newStar);

	}
}

void Background::Update(float offset)
{
	for (auto& star : Stars)
	{
		star.Update(offset);
	}
	
}

void Background::Render() const
{
	for (auto& star : Stars)
	{
		star.Render();
	}
}















