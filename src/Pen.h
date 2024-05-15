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

        Vertex mLineVertices[2];
        unsigned int mLineVBO;
        unsigned int mLineVAO;
        bool bDraw=false;
        bool bFirst=true;

        glm::vec3 screenToLocal(glm::vec2 screen);
    
};

Pen::Pen(){
    mVertices.push_back({glm::vec3(0.0f),glm::vec3(0.0f),glm::vec2(0.0f),glm::vec3(0.0f)});
    glGenVertexArrays(1,&mVAO);
    glGenBuffers(1,&mVBO);
    glGenBuffers(1,&mEBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER,mVBO);
    glBufferData(GL_ARRAY_BUFFER,mVertices.size()*sizeof(Vertex),&mVertices[0],GL_DYNAMIC_DRAW);
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,mIndice.size()*sizeof(unsigned int),&mIndice[0],GL_DYNAMIC_DRAW);
    

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

void Pen::Handle(){
    bDraw=true;
    DrawMesh();
}


void Pen::HandleOut(){
    bDraw=false;
}

void Pen::DrawMesh(){

    if(mVertices.size()<2)
        return;

    if(mVertices.size()==2){
        //glBindVertexArray(mVAO);
       // glDrawArrays(GL_LINE,0,2);

    }
    else{
        //glBindBuffer(GL_ARRAY_BUFFER,mVBO);
        //glDrawElements(GL_TRIANGLES,mIndice.size(),GL_UNSIGNED_INT,0);

        glBindVertexArray(mVAO);
        glDrawArrays(GL_TRIANGLES,0,mVertices.size());
    }

    // 라인을 그려줌
   // glBindVertexArray(mLineVAO);
   // glDrawArrays(GL_LINE,0,2);
}

void Pen::OnPointerDown(float xpos, float ypos,float xdelta,float ydelta){
    if(!bDraw)
        return;

    glm::vec3 point = screenToLocal(glm::vec2(xpos,ypos));
   // printf(" %f, %f, %f ",point.x,point.y,point.z);
    Vertex vert = {point,glm::vec3(1.0f),glm::vec2(1.0f),glm::vec3(1.0f)};
   
    if(glm::length(point-mVertices[0].Position) <= 0.1f &&mVertices.size()>3){
        //mesh로 만들어서 collection에 추가
        Mesh* mesh= new Mesh(mVertices,mIndice,std::vector<Texture>(0),NULL,NULL);
        Collection::GetInstance()->SetMesh(mesh);
        mVertices.clear();
        mIndice.clear();
    }
    else{
        mLineVertices[0] = vert;
        if(bFirst){
            mVertices[0] = vert;

        }
        else{
            if(mVertices.size()>=3){

            Vertex vert2 = mVertices[mVertices.size()-1];
            mVertices.push_back(mVertices[0]);
            mVertices.push_back(vert2);
            mVertices.push_back(vert);
            }
            mVertices.push_back(vert);
        }
        
        glBindVertexArray(mVAO);
        glBindBuffer(GL_ARRAY_BUFFER,mVBO);
        glBufferData(GL_ARRAY_BUFFER,mVertices.size()*sizeof(Vertex),&mVertices[0],GL_DYNAMIC_DRAW);


        if(mVertices.size()>=3){
            /*
            mIndice.push_back(0);
            mIndice.push_back(mVertices.size()-2);
            mIndice.push_back(mVertices.size()-1);

            for(int i=0;i<mIndice.size();i++){
                printf(" index %d :  %u  ", i,mIndice[i]);
            }
            printf("\n");

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,mIndice.size()*sizeof(unsigned int),&mIndice[0],GL_DYNAMIC_DRAW);
            */


        }
        

    }

    bFirst=false;
   
}

void Pen::OnMove(float xpos, float ypos,float xdelta,float ydelta){
    /*mLineVertices[1] = {glm::vec3(xpos,ypos,1.0f),glm::vec3(1.0f),glm::vec2(1.0f),glm::vec3(1.0f)};

    glBindVertexArray(mLineVAO);
    glBindBuffer(GL_ARRAY_BUFFER,mLineVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(mLineVBO),mLineVertices,GL_DYNAMIC_DRAW);*/
}

glm::vec3 Pen::screenToLocal(glm::vec2 screen){  //[TODO] 나중에 static으로 유틸함수로 빼버리기

    glm::vec4 ndcCoord;
    ndcCoord.x = (2.0f * screen.x) / SCR_WIDTH - 1.0f;
    ndcCoord.y = 1.0f - (2.0f * screen.y) / SCR_HEIGHT;
    ndcCoord.z = 0.0f-1.0f;
    ndcCoord.w = 1.0f;

    // NDC 좌표를 클립 공간 좌표로 변환
    glm::vec4 clipCoord = glm::inverse(projection) * ndcCoord;

    // 클립 공간 좌표를 월드 좌표로 변환
    glm::vec4 worldCoord = glm::inverse(view * glm::mat4(1.0f)) * clipCoord;

    if(worldCoord.w !=0.0f){
        worldCoord /= worldCoord.w;
    }
    

    return glm::vec3(worldCoord.x,worldCoord.y,0.0f);

}
