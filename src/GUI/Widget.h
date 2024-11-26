
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include "../constants.h"

#pragma once

class Widget
{
public:
    virtual ~Widget();
    virtual void Draw() = 0;
    bool GetVisible() const { return bVisible; }
    glm::vec3 GetPos() const { return mPos; }
    void SetPos(glm::vec3 offset);
    glm::vec2 GetSize() const { return glm::vec2(mSizeX, mSizeY); }
    eUIType GetType() const { return mType; }

protected:
    eUIType mType = eUIType::EMPTY;
    bool mPushed = false;
    glm::vec3 mPos;
    float mSizeX;
    float mSizeY;
    bool bVisible = true;
};


