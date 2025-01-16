#pragma once
#ifndef RESOURCES_H
#define RESOURCES_H



#include <string>
#include <array>
#include "raylib.h"
#include <vector>
#include <string_view>

struct GameTexture {
	Texture2D texture = {}; 
	explicit GameTexture(std::string_view path) {
		texture = LoadTexture(path.data()); 
	}

GameTexture(const GameTexture&) = delete; 
GameTexture& operator=(const GameTexture&) = delete;

 GameTexture(GameTexture&& other) noexcept : texture(other.texture) {
        other.texture = {}; // Leave the moved-from object in a valid state
    }
    GameTexture& operator=(GameTexture&& other) noexcept {
        if (this != &other) {
            UnloadTexture(texture); // Clean up current texture
            texture = other.texture;
            other.texture = {}; // Leave the moved-from object in a valid state
        }
        return *this;
    }


	~GameTexture() {
		 if (texture.id != 0) {
            UnloadTexture(texture);
        }
		
	
	
};


struct Resources
{
	std::array<GameTexture, 3> shipTextures = { GameTexture("./Assets/Ship1.png"), GameTexture("./Assets/Ship2.png"), GameTexture("./Assets/Ship3.png") };
	GameTexture alienTexture = GameTexture("./Assets/Alien.png");
	GameTexture barrierTexture = GameTexture("./Assets/Barrier.png");
	GameTexture laserTexture = GameTexture("./Assets/Laser.png");

	Resources()
        : shipTextures{
            GameTexture("./Assets/Ship1.png"),
            GameTexture("./Assets/Ship2.png"),
            GameTexture("./Assets/Ship3.png")
          },
          alienTexture("./Assets/Alien.png"),
          barrierTexture("./Assets/Barrier.png"),
          laserTexture("./Assets/Laser.png") {}

    // Destructor: Automatically cleans up all resources
    ~Resources() = default;
};


#endif // !RESOURCES_h




