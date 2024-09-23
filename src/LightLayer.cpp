#include "LightLayer.h"

LightLayer::LightLayer(std::string name, glm::vec3 lightColor, glm::vec3 pos)
{
    this->name = name;
    layerType = eLayerType::LIGHT;
    mLightColor = lightColor;
    SetPosition(pos);
}

void LightLayer::SetPosition(glm::vec3 pos)
{
    Layer::SetPosition(pos);
}

void LightLayer::SetRotation(glm::vec3 rot)
{
}

void LightLayer::SetScale(glm::vec3 scale)
{
}

void LightLayer::SetColor(glm::vec3 color)
{
    mLightColor=color;
}
void LightLayer::SetIndex(unsigned int i)
{
    mLayerIndex = i;
}
void LightLayer::Draw()
{
    unsigned int uniformOffset = mLayerIndex * LIGHT_SIZE;
    glBufferSubData(GL_UNIFORM_BUFFER, uniformOffset + 16, sizeof(float) * 3, glm::value_ptr(GetPosition()));
    glBufferSubData(GL_UNIFORM_BUFFER, uniformOffset, sizeof(float) * 3, glm::value_ptr(mLightColor));
}