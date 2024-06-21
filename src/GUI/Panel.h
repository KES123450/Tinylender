
#include "Widget.h"
#include <glm/glm.hpp>
#include "../Shader/Shader.h"
#include "../stb_image.h"

#pragma once

class Panel :public Widget{

    public:
        Panel(glm::vec3 buttonPos,float sizeX, float sizeY, const char *texPath);

        void Draw() override;
       
    private:
        Shader UIShader;
        unsigned int mVBO;
        unsigned int mVAO;
        unsigned int mEBO;
        unsigned int mTexture;
        int mWidth, mHeight, mMinimaps;
        float mVertexArray[20];
        glm::vec4 mColor= glm::vec4(1.0f,1.0f,1.0f,1.0f);
        unsigned int mIndices[6]={
            0,1,2,
            2,1,3
        };
};

