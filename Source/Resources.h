#pragma once
#include "raylib.h"
#include "vector"


struct Resources 
{
public: 

	void Load();

	Resources(); 
	~Resources(); 

	std::vector<Texture2D> shipTextures;
	Texture2D alienTexture;
	Texture2D barrierTexture;
	Texture2D laserTexture;

};