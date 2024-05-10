#include <glm/glm.hpp>
#include <string>

#pragma once

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Color;
};

struct Texture{
    unsigned int id;
    std::string type;
};