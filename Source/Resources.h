#pragma once
#ifndef RESOURCES_H
#define RESOURCES_H



#include <string>
#include "raylib.h"
#include "vector"
#include "Texture.h"


class Resources
{
public:

	Texture alienTexture;
	Texture barrierTexture;
	Texture laserTexture;
	std::vector<Texture2D> shipTextures;

	Resources(); 

};  


#endif // !RESOURCES_h




