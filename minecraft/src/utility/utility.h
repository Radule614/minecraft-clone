#pragma once

#include <iostream>
#include "glm/glm.hpp"

namespace utility{
	
    void printVec3(glm::vec3& vec)
    {
        std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
    }

    void print2Vec3(glm::vec3& vec1, glm::vec3& vec2)
    {
        std::cout << "(" << vec1.x << ", " << vec1.y << ", " << vec1.z << ") == ";
        std::cout << "(" << vec2.x << ", " << vec2.y << ", " << vec2.z << ")" << std::endl;
    }
}