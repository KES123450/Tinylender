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


Model::Model(std::string path,const GLchar* vertexPath,const GLchar* fragPath)
{
    mVertexPath = vertexPath;
    mFragPath = fragPath;
    loadModel(path);
}

Model::~Model()
{
}

void Model::Draw(){
    for(unsigned int i=0; i<mMeshes.size(); i++){
        mMeshes[i].Draw();
    }

}

void Model::loadModel(std::string path){
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        printf("%s",import.GetErrorString());
        return;
    }
    
    mDirectory = path.substr(0,path.find_last_of('/'));
    processNode(scene->mRootNode,scene);
}

void Model::processNode(aiNode *node, const aiScene *scene){

    for(unsigned int i=0;i<node->mNumMeshes;i++){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        mMeshes.push_back(processMesh(mesh,scene));
    }

    for(unsigned int i=0; i<node->mNumChildren; i++){
        processNode(node->mChildren[i],scene);
    }

}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene){
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indice;
    std::vector<Texture> textures;

    for(unsigned int i=0;i<mesh->mNumVertices;i++){
        Vertex vertex;
        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if(mesh->mTextureCoords[0]){
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords=vec;
        }
        else{
            vertex.TexCoords = glm::vec2(0.0f,0.0f);
        }

        vertices.push_back(vertex);
    }

    for(unsigned int i=0; i<mesh->mNumFaces;i++){
        aiFace face = mesh->mFaces[i];
        for(unsigned int j=0;j<face.mNumIndices;j++){
            indice.push_back(face.mIndices[j]);
        }
    }

    std::vector<std::vector<unsigned int>> face;

    return Mesh(vertices,indice,textures,face,mVertexPath,mFragPath);
}