#include "Layer.h"

void Layer::SetPosition(glm::vec3 pos)
{
    mPosition = pos;
}

void Layer::SetRotation(glm::vec3 rot)
{
    mRotation = rot;
}

void Layer::SetScale(glm::vec3 scale)
{
    mScale = scale;
}

void Layer::SetVisible(bool v)
{
    mVisible = v;
}