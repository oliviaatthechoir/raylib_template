#include "Resources.h"
#include <iostream>;

void Resources::Load()
{
	std::cout << "Loading resources...\n";
	alienTexture = LoadTexture("./Assets/Alien.png");
	barrierTexture = LoadTexture("./Assets/Barrier.png");

	shipTextures.push_back(LoadTexture("./Assets/Ship1.png"));
	shipTextures.push_back(LoadTexture("./Assets/Ship2.png"));
	shipTextures.push_back(LoadTexture("./Assets/Ship3.png"));

	laserTexture = LoadTexture("./Assets/Laser.png");
}

Resources::~Resources() {

	UnloadTexture(alienTexture);
	UnloadTexture(barrierTexture);
	UnloadTexture(laserTexture);

	for (const auto& texture : shipTextures) {
		UnloadTexture(texture);
	}
}