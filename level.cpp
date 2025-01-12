#include <iostream>
#include <fstream>
#include <vector> 
#include <string>
#include "level.h"


void Entity::LoadLevelFromAFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    file >> x >> y; 

    if (file.fail()) {
        std::cerr << "Error: Failed to read position from file " << filename << std::endl;
    }

   
}
