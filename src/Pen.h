#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Vertex.h"
#include "IPressedDown.h"
#include "IPressedUp.h"


#pragma once


class Pen: public IPressedDown, public IPressedUp{
    public:
        void DrawMesh();
    
    private:
        std::vector<Vertex> mVertices;
        std::vector<unsigned int> mIndice;
        unsigned int mVBO;
        unsigned int mVAO;
        unsigned int mEBO;
        bool bDraw;
        glm::vec2 mHandlePoint;
    
};

void Pen::DrawMesh(){
    if(!bDraw)
        return;
    
    if(mVertices.size()==0)
        return;

    if(mVertices.size()<3){
        glBindVertexArray(mVAO);
        glDrawArrays(GL_LINE,0,2);

    }
    else{
        glBindVertexArray(mVAO);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    }
}


