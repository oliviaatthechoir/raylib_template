#pragma once
#include "raylib.h"
#include "vector"


struct Resources 
{
public: 
	Resources(); 
	~Resources(); 

	void Load();


	std::vector<Texture2D> shipTextures;
	Texture2D alienTexture;
	Texture2D barrierTexture;
	Texture2D laserTexture;

};

