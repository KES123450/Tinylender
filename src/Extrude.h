#include "IState.h"
#include "IPressedDown.h"
#include "IPressed.h"
#include "IPressedUp.h"
#include "Collection.h"
#include "Mesh.h"
#include "Vertex.h"
#include <vector>
#include <glm/glm.hpp>

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
        void selectFace();
        void extrudeMesh(float xdelta, float ydelta);
        void calculateVertexNormal();
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

}

void Extrude::OnPointerUp(float xpos, float ypos,float xdelta,float ydelta){
    if(!bState)
        return;

    mCurrentVertices.clear();
    mNewVertices.clear();
    mVertices.clear();
    mFaces.clear();
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
    Mesh* mesh = Collection::GetInstance()->GetSelectedMesh(); 

    glm::vec3 faceNormal = glm::vec3(0.3f,0.8f,0.7f);
    for(int i=0;i<mNewVertices.size();i++){
        mNewVertices[i].Position.x = (mNewVertices[i].Position.x -(faceNormal.x*((ydelta+xdelta)/2))*0.03f);
        mNewVertices[i].Position.y = (mNewVertices[i].Position.y -(faceNormal.y*((ydelta+xdelta)/2))*0.03f);
        mNewVertices[i].Position.z = (mNewVertices[i].Position.z -(faceNormal.z*((ydelta+xdelta)/2))*0.03f);
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
        resultVertices.push_back(mVertices[i]);
        resultVertices.push_back(mVertices[i+vertexNum]);
        resultVertices.push_back(mVertices[(i+1)%vertexNum+vertexNum]);

        resultVertices.push_back(mVertices[i]);
        resultVertices.push_back(mVertices[(i+1)%vertexNum+vertexNum]);
        resultVertices.push_back(mVertices[(i+1)%vertexNum]);
    }

    mesh->vertices = resultVertices;

    mesh->SetMesh();

}


