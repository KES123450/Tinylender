#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include "../stb_image.h"
#include "Widget.h"
#include "../constants.h"
#include "../Shader/Shader.h"

#pragma once

class Button : public Widget
{
public:
    Button(glm::vec3 buttonPos, float sizeX, float sizeY, const char *texPath, eImageType imageType);
    void Draw() override;
    bool GetPushed() const { return mPushed; }
    void Pushed();
    void SetTexture(const char *texPath, eImageType imageType);
    void SetbuttonCallback(std::function<void(double xpos, double ypos)> callback);
    std::function<void(double xpos, double ypos)> getButtonCallback() const { return mbuttonCallback; }
    void Callbtn();


private:
    Shader UIShader;
    unsigned int mVBO;
    unsigned int mVAO;
    unsigned int mEBO;
    unsigned int mTexture;
    int mWidth, mHeight, mMinimaps;
    float mVertexArray[20];
    std::function<void(double xpos, double ypos)> mbuttonCallback = NULL;
    glm::vec4 mColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    unsigned int mIndices[6] = {
        0, 1, 2,
        2, 1, 3};
};
