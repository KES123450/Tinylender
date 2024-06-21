

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <algorithm>
#include "Vertex.h"
#include "Mesh.h"
#include "IPressedDown.h"
#include "IPressed.h"
#include "IPressedUp.h"
#include "IMoved.h"
#include "IState.h"
#include "Collection.h"
#include "ShapeLayer.h"
#include "constants.h"

#pragma once
extern glm::mat4 view;
extern glm::mat4 projection;
extern glm::vec3 cameraFront;

class Pen: public IPressedDown,public IMoved,public IState{
    public:
        Pen();
        void DrawMesh();
        void OnPointerDown(float xpos, float ypos,float xdelta,float ydelta) override;
        void OnMove(float xpos, float ypos,float xdelta,float ydelta) override;
        void Handle() override;
        void HandleOut() override;
    
    private:
        std::vector<Vertex> mVertices;
        std::vector<unsigned int> mIndice;
        unsigned int mVBO;
        unsigned int mVAO;
        unsigned int mEBO;

        float mLineVertices[9] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f};
    
        unsigned int mLineVBO;
        unsigned int mLineVAO;
        bool bDraw=false;
        bool bFirst=true;

        glm::vec3 screenToLocal(glm::vec2 screen);
    
};
