

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "Widget.h"
#include "../Layer.h"
#include "../constants.h"
#include "../Shader/Shader.h"
#include "../stb_image.h"
#pragma once

class LayerUI: public Widget{
    public:
        LayerUI(Layer* layer,float layerSizeX,float layerSizeY,glm::vec3 layerPos);
        void Draw() override;
        Layer* GetLayer() const {return mLayer;}
        std::vector<LayerUI*> children;
        void SelectLayerUI();
        void UnSelectLayerUI();
        void SetTexture(const char *texPath,eImageType imageType);

    private:
        Shader* mLayerUIShader;
        bool bSelected=false;
        bool bDragged=false;
        Layer* mLayer;

        unsigned int mVBO;
        unsigned int mVAO;
        unsigned int mEBO;
        const char *mTexPath="resource/Layer.jpg";
        unsigned int mTexture;
        int mWidth, mHeight, mMinimaps;
        float mVertexArray[20];
        unsigned int mIndices[6]={
        0,1,2,
        2,1,3
    };
};