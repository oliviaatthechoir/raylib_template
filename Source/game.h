#pragma once
#include "raylib.h"
#include <vector>
#include "Resources.h"
#include <string>


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




struct Projectile
{
public: 
	// INITIALIZE PROJECTILE WHILE DEFINING IF ITS PLAYER OR ENEMY 
	Vector2 position = {0,0};
	int speed = 15; 
	bool active = true;  
	EntityType type = {};

	// LINE WILL UPDATE WITH POSITION FOR CALCULATIONS
	Vector2 lineStart = { 0, 0 };
	Vector2 lineEnd = { 0, 0 };

	void Update();

	void Render(GameTexture& texture) const;
};

struct Wall 
{
public: 
	Vector2 position; 
	Rectangle rec; 
	bool active; 
	Color color; 
	int health = 50;
	int radius = 60;


	void Render(GameTexture& texture) const; 
	void Update(); 
};

struct Alien
{
public:
	
	Color color = WHITE; 
	Vector2 position = {0, 0};
	int x = 0; 
	int y = 0; 
	float radius = 30;
	bool active = true;  
	bool moveRight = true; 
	
	EntityType type = EntityType::ENEMY; 

	int speed = 2; 
		 
	void Update(); 
	void Render(Texture2D texture) const; 
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

	

	// Gamestate
	State gameState = State::STARTSCREEN; 

	// Score
	int score;

	// for later, make a file where you can adjust the number of walls (config file) 
	int wallCount = 5;

	//Aliens shooting
	

	Rectangle rec = { 0, 0 ,0 ,0 }; 

	

	bool newHighScore = false;
	

	void Start();
	void End();

	void Continue();
	
	void Launch() const; 

	void Update();

	void HandleStartScreen(); 
	void HandleGamePlay(); 
	void HandleEndScreen(); 

	void Render();
	void RenderStartScreen() const; 
	void RenderGamePlay(); 
	void RenderEndScreen(); 

	void RenderHighScoreInput() const;
	void RenderCursorBlink() const;
	void RenderLeaderboard(); 

	void SpawnAliens();

	bool CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineTop, Vector2 lineBottom) const;

	bool CheckNewHighScore();

	void InsertNewHighScore(const std::string_view& name);


	void SaveLeaderboard() const;


	// Entity Storage and Resources

	Resources resources;


	std::vector<Projectile> Projectiles;

	std::vector<Wall> Walls;

	

	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };
	
	Background background;


	Vector2 playerPos;
	Vector2 alienPos; 
	Vector2 cornerPos;
	float offset;

	int formationWidth = 8;
	int formationHeight = 5;
	int alienSpacing = 80;
	int formationX = 100;
	int formationY = 50;


	//TEXTBOX ENTER
	std::string name = "";     //One extra space required for null terminator char '\0'
	int letterCount = 0;

	Rectangle textBox = { 600, 500, 225, 50 };
	bool mouseOnText = false;

	int framesCounter = 0;

	bool operator==(const Game& other) const = default;
};