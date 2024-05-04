#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Vertex.h"
#include "Shader/Shader.h"

#pragma once

class Mesh{
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indice;
        std::vector<Texture> textures;
        void Draw();

    private:
        void setMesh();
        unsigned int mVAO, mVBO, mEBO;
        Shader mShader;
        


};

void Mesh::setMesh(){

    glGenVertexArrays(1,&mVAO);
    glGenBuffers(1,&mVBO);
    glGenBuffers(1,&mEBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER,mVBO);
    glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(Vertex),vertices,GL_DYNAMIC_DRAW);
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indice.size()*sizeof(unsigned int),indeices,GL_DYNAMIC_DRAW);
    

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);
    
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,Normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,TexCoord));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,Color));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}