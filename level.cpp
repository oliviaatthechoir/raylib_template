#include <iostream>
#include <fstream>
#include <vector> 
#include <string>
#include "level.h"

void Entity::Print() const {
    std::cout << "Entity Position: (" << x << ", " << y << ")" << '\n';
}


Entity LoadLevelFromAFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << '\n';
    }

    float x = 0.0f; 
    float y = 0.0f;
    file >> x >> y; 

    if (file.fail())
    {
        std::cerr << "error: failed to read position from file" + filename; 
    }

    return Entity(x,y);
}
