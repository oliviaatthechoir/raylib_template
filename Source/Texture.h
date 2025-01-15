#pragma once
#include "raylib.h"
#include <string>

class Texture {
public: 
	Texture2D texture;

	Texture(const std::string& path) {
		texture = LoadTexture(path.c_str());

	}

	~Texture() {
		UnloadTexture(texture);
	}
};