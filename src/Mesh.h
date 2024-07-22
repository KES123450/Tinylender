
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
        unsigned int GetVAO() const {return mVAO;}
        std::vector<Texture> GetTexture() const {return textures;}
        int GetVerticeCount() const {return vertices.size();}

    private:
        unsigned int mVAO, mVBO, mEBO;
        Shader mShader;
        
};

