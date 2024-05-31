#include "IState.h"
#include "IPressedDown.h"
#include "IPressed.h"
#include "IPressedUp.h"
#include "Collection.h"
#include "Mesh.h"
#include "Vertex.h"
#include <vector>
#include <glm/glm.hpp>
#include <iostream>

#pragma once

class Extrude:public IState, public IPressedDown ,public IPressed, public IPressedUp{
    public:
        void Handle() override;
        void HandleOut() override;
        void OnPointerDown(float xpos, float ypos,float xdelta,float ydelta) override;
        void OnPointer(float xpos, float ypos,float xdelta,float ydelta) override;
        void OnPointerUp(float xpos, float ypos,float xdelta,float ydelta) override;

    private:
        bool bState=false;
        std::vector<Vertex> mCurrentVertices;
        std::vector<Vertex> mNewVertices;
        std::vector<Vertex> mVertices;
        std::vector<std::vector<unsigned int>> mFaces;
        std::vector<glm::vec3> mFacesNormal;

        void selectFace();
        void extrudeMesh(float xdelta, float ydelta);
        void setVertexNormal();
};

void Extrude::Handle(){
    bState=true;
}

void Extrude::HandleOut(){
    bState=false;
}

void Extrude::OnPointer(float xpos, float ypos,float xdelta,float ydelta){
    if(!bState)
        return;
    
    extrudeMesh(xdelta,ydelta);
}

void Extrude::OnPointerDown(float xpos, float ypos,float xdelta,float ydelta){
    if(!bState)
        return;
    
    selectFace();

    unsigned int vertexNum = (mCurrentVertices.size()/3)+2;
    mVertices.push_back(mCurrentVertices[0]);
    mVertices.push_back(mCurrentVertices[1]);
    mVertices.push_back(mCurrentVertices[2]);
    for(int i=1;i<vertexNum-2;i++){
        mVertices.push_back(mCurrentVertices[3*i+2]);
    }

    //여기서부터 쓰레기값
    mVertices.push_back(mCurrentVertices[vertexNum]);
    mVertices.push_back(mCurrentVertices[vertexNum+1]);
    mVertices.push_back(mCurrentVertices[vertexNum+2]);
    for(int i=1;i<vertexNum-2;i++){
        mVertices.push_back(mCurrentVertices[3*i+2]);
    }

    setVertexNormal();
    
}
void Extrude::OnPointerUp(float xpos, float ypos,float xdelta,float ydelta){
    if(!bState)
        return;

    mCurrentVertices.clear();
    mNewVertices.clear();
    mVertices.clear();
}

void Extrude::selectFace(){
    Mesh* mesh = Collection::GetInstance()->GetSelectedMesh();
    std::vector<unsigned int> faceIdx = mesh->faces[0]; // 일단 무조건 0번 면을 가져오도록 하드코딩

    for(int i=0;i<faceIdx.size()/3;i++){
        unsigned int idx = faceIdx[i*3];
        Vertex v = mesh->vertices[idx];
        mCurrentVertices.push_back(v);
    }

    mNewVertices=mCurrentVertices;
}

void Extrude::extrudeMesh(float xdelta, float ydelta){

    if(glm::length(mNewVertices[0].Position-mCurrentVertices[0].Position)<=0.0f){
        return;
    }

    Mesh* mesh = Collection::GetInstance()->GetSelectedMesh(); 

    glm::vec3 faceNormal = glm::normalize(glm::cross(
        mCurrentVertices[1].Position-mCurrentVertices[0].Position,
        mCurrentVertices[2].Position-mCurrentVertices[1].Position));


    for(int i=0;i<mNewVertices.size();i++){
        mNewVertices[i].Position.x = (mNewVertices[i].Position.x -(faceNormal.x*((ydelta+xdelta)/2))*0.03f);
        mNewVertices[i].Position.y = (mNewVertices[i].Position.y -(faceNormal.y*((ydelta+xdelta)/2))*0.03f);
        mNewVertices[i].Position.z = (mNewVertices[i].Position.z -(faceNormal.z*((ydelta+xdelta)/2))*0.03f);
        mNewVertices[i].Normal=faceNormal;
    }

    std::vector<Vertex> resultVertices = mCurrentVertices;
    std::vector<Vertex>::iterator it = resultVertices.end();
    resultVertices.insert(it,mNewVertices.begin(),mNewVertices.end());

    unsigned int vertexNum = (mCurrentVertices.size()/3)+2;
    
    mVertices[vertexNum]=mNewVertices[0];
    mVertices[vertexNum+1]=mNewVertices[1];
    mVertices[vertexNum+2]=mNewVertices[2];
    for(int i=1;i<vertexNum-2;i++){
        mVertices[vertexNum+2+i]=mNewVertices[3*i+2];
    }


    for(int i=0;i<vertexNum;i++){
        Vertex vert = {glm::vec3(1.0f),mFacesNormal[i+2],glm::vec2(1.0f),glm::vec3(1.0f)};
        vert.Position = mVertices[i].Position;
        resultVertices.push_back(vert);

        vert.Position = mVertices[i+vertexNum].Position;
        resultVertices.push_back(vert);

        vert.Position = mVertices[(i+1)%vertexNum+vertexNum].Position;
        resultVertices.push_back(vert);

        vert.Position = mVertices[i].Position;
        resultVertices.push_back(vert);

        vert.Position = mVertices[(i+1)%vertexNum+vertexNum].Position;
        resultVertices.push_back(vert);

        vert.Position = mVertices[(i+1)%vertexNum].Position;
        resultVertices.push_back(vert);
    }

    mesh->vertices = resultVertices;

    mesh->SetMesh();
}

void Extrude::setVertexNormal(){
    unsigned int vertexNum = (mCurrentVertices.size()/3)+2;

    glm::vec3 faceNormal = glm::normalize(glm::cross(
        mVertices[1].Position-mVertices[0].Position,
        mVertices[2].Position-mVertices[1].Position));

    for(int i=0;i<mCurrentVertices.size();i++){
        mCurrentVertices[i].Normal=glm::vec3(-faceNormal.x,-faceNormal.y,-faceNormal.z);
    }

    std::vector<unsigned int> upFace;
    for(int i=0;i<vertexNum;i++){
        upFace.push_back(i);
    }
    mFaces.push_back(upFace);
    mFacesNormal.push_back(faceNormal);

    std::vector<unsigned int> downFace;
    for(int i=vertexNum;i<vertexNum*2;i++){
        downFace.push_back(i);
    }
    mFaces.push_back(downFace);
    mFacesNormal.push_back(glm::vec3(-faceNormal.x,-faceNormal.y,-faceNormal.z));

    
    for(int i=0;i<mNewVertices.size();i++){
        mNewVertices[i].Position.x = (mNewVertices[i].Position.x -(faceNormal.x*0.1f));
        mNewVertices[i].Position.y = (mNewVertices[i].Position.y -(faceNormal.y*0.1f));
        mNewVertices[i].Position.z = (mNewVertices[i].Position.z -(faceNormal.z*0.1f));
    }

    mVertices[vertexNum]=mNewVertices[0];
    mVertices[vertexNum+1]=mNewVertices[1];
    mVertices[vertexNum+2]=mNewVertices[2];
    for(int i=1;i<vertexNum-2;i++){
        mVertices[vertexNum+2+i]=mNewVertices[3*i+2];
    }

    for(int i=0;i<vertexNum;i++){

        std::vector<unsigned int> face;
        face.push_back(i);
        face.push_back(i+vertexNum);
        face.push_back((i+1)%vertexNum+vertexNum);
        face.push_back((i+1)%vertexNum);
        mFaces.push_back(face);
        mFacesNormal.push_back(glm::normalize(glm::cross(
            mVertices[(i+1)%vertexNum].Position-mVertices[i].Position,
            mVertices[i+vertexNum].Position-mVertices[i].Position
        )));
    }

/*
    for(int index=0;index<mCurrentVertices.size();++index){
        glm::vec3 sum = glm::vec3(0.0f);
        int k;
        if (index % 3 == 0) {
            k=0;
        } else {
            k=index / 3 + index % 3;
        }

        for(int i=0;i<faces.size();i++){
            for(int j=0;j<faces[i].size();j++){
                if(faces[i][j]==k){
                    sum+=facesNormal[i];
                    break;
                }
            }
        }
        mCurrentVertices[index].Normal= glm::normalize(sum);
    }

    for(int index=0;index<mNewVertices.size();++index){
        glm::vec3 sum = glm::vec3(0.0f);
        int k;
        if (index % 3 == 0) {
            k=0;
        } else {
            k=index / 3 + index % 3;
        }

        for(int i=0;i<faces.size();i++){
            for(int j=0;j<faces[i].size();j++){
                if(faces[i][j]==k+vertexNum){
                    sum+=facesNormal[i];
                    break;
                }
            }
        }
        mNewVertices[index].Normal= glm::normalize(sum);
    }*/
}

