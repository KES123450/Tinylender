#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Layer.h"
#include "constants.h"
#include "Shader/Shader.h"

#pragma once

class LightLayer : public Layer
{
public:
    LightLayer() {};
    LightLayer(std::string name, glm::vec3 lightColor, glm::vec3 pos);
    void SetPosition(glm::vec3 pos);
    void SetRotation(glm::vec3 rot);
    void SetScale(glm::vec3 scale);
    void SetColor(glm::vec3 color);
    void SetIndex(unsigned int i);
    void Draw();

private:
    glm::vec3 mLightColor;
    unsigned int mLayerIndex;
};