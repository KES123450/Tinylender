
#include <vector>
#include "Mesh.h"
#include <string>
#include "Shader/Shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma once
class Model
{
    public:
        Model(std::string path,const GLchar* vertexPath,const GLchar* fragPath);
        ~Model();
        std::vector<Mesh>* GetMeshes() {return &mMeshes;}
        void Draw();

    private:
        const GLchar* mVertexPath;
        const GLchar* mFragPath;
        std::vector<Mesh> mMeshes;
        std::string mDirectory;
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);

};

