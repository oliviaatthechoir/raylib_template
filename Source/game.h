#pragma once
#include "raylib.h"
#include "Alien.h"
#include "Player.h"

#include <vector>
#include "Resources.h"
#include <string>
#include "Walls.h"


enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};

enum struct EntityType
{
	PLAYER,
	ENEMY,
	PLAYER_PROJECTILE,
	ENEMY_PROJECTILE
};

struct PlayerData
{
	std::string name;
	int score;
};


struct Star
{
	Vector2 initPosition = { 0, 0 };
	Vector2 position = { 0, 0 };
	Color color = GRAY;
	float size = 0;
	void Update(float starOffset);
	void Render() const;
};

struct Background
{
	std::vector<Star> Stars;

	void Initialize(int starAmount);
	void Update(float offset);
	void Render() const;

};

struct Game
{
	int score;
	State gameState = State::STARTSCREEN; 
	bool newHighScore = false;

	Resources resources;
	Background background;

	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };

	int formationWidth = 8;
	int formationHeight = 5;
	int alienSpacing = 80;
	int formationX = 100;
	int formationY = 50;

	//Core functions 
	void Start();
	void End();
	void Continue();
	void Update();
	void Render();
	void SpawnAliens(std::vector<Alien>& aliens); 

	// Update functions 
	void HandleStartScreen(); 
	void HandleGamePlay(); 
	void HandleEndScreen(); 


	// Rendering core loop functions 
	void RenderStartScreen() const;
	void RenderGamePlay(const std::vector<Alien>& aliens, const std::vector<Projectile>& projectiles, const std::vector<Wall>& wall, const Player& player);
	void RenderEndScreen();
	
	// Score functions 
	void InsertNewHighScore(const std::string_view& name);
	bool CheckNewHighScore();
	void SaveLeaderboard() const;
	
	// UI functions 
	void RenderHighScoreInput() const;
	void RenderCursorBlink() const;
	void RenderLeaderboard(); 



	//TEXTBOX ENTER
	std::string name = "";     //One extra space required for null terminator char '\0'
	int letterCount = 0;

	Rectangle textBox = { 600, 500, 225, 50 };
	bool mouseOnText = false;

	int framesCounter = 0;

	bool operator==(const Game& other) const = default;
};