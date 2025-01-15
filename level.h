#pragma once 
#include <iostream>
#include <string>

struct Entity
{
	float x = 0.0f;
	float y = 0.0f;

	Entity() = default; 
	Entity(float x, float y) : x(x), y(y) {}

	void Print() const;
		


};

Entity LoadLevelFromAFile(const std::string& filename); 