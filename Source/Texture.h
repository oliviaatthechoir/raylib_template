#pragma once
#include "raylib.h"
#include <string>

class Texture {
public: 
	Texture2D texture;

	Texture(const std::string_view path) {
		texture = LoadTexture(path.data());

	}

	~Texture() {
		UnloadTexture(texture);
	}
};