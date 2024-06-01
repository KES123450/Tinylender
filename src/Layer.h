#include <string>
#include <vector>
#include <glm/glm.hpp>

#pragma once

class Layer{
    public:
        std::string name;
        std::vector<Layer*> children;
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);

        bool visible = true;
}