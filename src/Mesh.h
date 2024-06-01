#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Vertex.h"
#include "Shader/Shader.h"

#pragma once

class Mesh{
    public:
        Mesh(std::vector<Vertex> vert,
        std::vector<unsigned int> idx,
        std::vector<Texture> tex,
        std::vector<std::vector<unsigned int>> fcs,
        const GLchar* vertexPath,
        const GLchar* fragPath
        );

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indice;
        std::vector<Texture> textures;
        std::vector<std::vector<unsigned int>> faces;
        void Draw();
        void DrawSelected();
        void SetMesh();
        unsigned int GetVBO() const {return mVBO;}

    private:
        unsigned int mVAO, mVBO, mEBO;
        Shader mShader;
        
};

Mesh::Mesh(
    std::vector<Vertex> vert,
    std::vector<unsigned int> idx,
    std::vector<Texture> tex,
    std::vector<std::vector<unsigned int>> fcs,
    const GLchar* vertexPath,
    const GLchar* fragPath) : mShader(vertexPath, fragPath) {
        vertices=vert;
        indice = idx;
        textures = tex;
        faces= fcs;
        SetMesh();
}

void Mesh::SetMesh(){

    glGenVertexArrays(1,&mVAO);
    glGenBuffers(1,&mVBO);
    glGenBuffers(1,&mEBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER,mVBO);
    glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(Vertex),&vertices[0],GL_DYNAMIC_DRAW);
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indice.size()*sizeof(unsigned int),&indice[0],GL_DYNAMIC_DRAW);
    

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);
    
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,Normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,TexCoords));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,Color));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}

void Mesh::Draw(){
    for(unsigned int i=0;i<textures.size();i++){
        glActiveTexture(GL_TEXTURE0+i);
        glBindTexture(GL_TEXTURE_2D,textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBindVertexArray(mVAO);
    if(indice.size()>0){
        glDrawElements(GL_TRIANGLES,indice.size(),GL_UNSIGNED_INT,0);
    }
    else{
         glDrawArrays(GL_TRIANGLES,0,vertices.size());
    }
    
    for(int i=0;i<vertices.size(); i++){

        //printf("  %f, %f, %f  ",vertices[i].Position.x,vertices[i].Position.y,vertices[i].Position.z);
    }
}

void Mesh::DrawSelected(){
    mShader.use();
    for(unsigned int i=0;i<textures.size();i++){
        glActiveTexture(GL_TEXTURE0+i);
        glBindTexture(GL_TEXTURE_2D,textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES,indice.size(),GL_UNSIGNED_INT,0);
   
}