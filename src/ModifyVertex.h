#include <glm/glm.hpp>
#include "Collection.h"
#include "IPressed.h"
#include "IPressedDown.h"
#include "IPressedUp.h"
#include "IState.h"
#include "Mesh.h"
#include "Vertex.h"
#include "constants.h"

#pragma once

extern glm::mat4 view;
extern glm::mat4 projection;
extern glm::vec3 cameraFront;

class ModifyVertex:public IPressedDown,public IPressed, public IPressedUp,public IState{
    public:
        void OnPointer(float xpos, float ypos,float xdelta,float ydelta) override;
        void OnPointerDown(float xpos, float ypos,float xdelta,float ydelta) override;
        void OnPointerUp(float xpos, float ypos,float xdelta,float ydelta) override;
        void Handle() override;

    private:
        bool bPushed=false;
        bool bFindVertex = false;
        float mDeltaX, mDeltaY;
        int mSelectedIdx=0;
        glm::vec2 coordinatelocalToScreen(float x,float y, float z);
        bool searchVertex(float xpos, float ypos);
};


void ModifyVertex::Handle(){
    Mesh* m = Collection::GetInstance()->GetSelectedMesh();

    if(bPushed&&bFindVertex){
        printf("%s"," in ");
        Mesh* selectMesh = Collection::GetInstance()->GetSelectedMesh();
        unsigned int VBO = Collection::GetInstance()->GetSelectedMesh() -> GetVBO();
        glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f);
        glm::vec3 right = glm::normalize(glm::cross(up,-(cameraFront)));

        Vertex offset = selectMesh->vertices[mSelectedIdx];
        // printf(" deltaX : %f ", mDeltaX);
        // printf(" deltaY : %f ", mDeltaY);
        // printf(" before positionX : %f ", offset.Position.x);
        // printf(" before positionY : %f ", offset.Position.y);
        // printf(" before positionZ : %f ", offset.Position.z);
        offset.Position.x += mDeltaX*right.x *0.001f;
        offset.Position.y += -mDeltaY*0.001f;
        offset.Position.z += mDeltaX*right.z*0.001f;
        // printf(" after positionX : %f ", offset.Position.x);
        // printf(" after positionY : %f ", offset.Position.y);
        // printf(" after positionZ : %f ", offset.Position.z);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferSubData(GL_ARRAY_BUFFER,mSelectedIdx*sizeof(Vertex),sizeof(offset),&offset);

        selectMesh->vertices[mSelectedIdx].Position.x += mDeltaX*right.x*0.001f;
        selectMesh->vertices[mSelectedIdx].Position.y += -mDeltaY*0.001f;
        selectMesh->vertices[mSelectedIdx].Position.z += mDeltaX*right.z*0.001f;
    }

}

void ModifyVertex::OnPointerDown(float xpos, float ypos,float xdelta,float ydelta){
    bPushed=true;
    printf("%s","pushed");
    if(searchVertex(xpos, ypos)){
        printf("%s","find");
        bFindVertex=true;
    }
}

void ModifyVertex::OnPointer(float xpos, float ypos,float xdelta,float ydelta){
    printf(" xpos : %f ", xpos);
    printf(" ypos  : %f ", ypos);
    printf(" xdelta : %f ", xdelta);
    printf(" ydelta : %f ", ydelta);

    mDeltaX=xdelta;
    mDeltaY=ydelta;
}

void ModifyVertex::OnPointerUp(float xpos, float ypos,float xdelta,float ydelta){
    bPushed=false;
    bFindVertex=false;
}


glm::vec2 ModifyVertex::coordinatelocalToScreen(float x,float y, float z){
    glm::vec4 local = glm::vec4(x,y,z,1.0f);
    glm::vec4 viewCoord = view*local;
    glm::vec4 clipCoord = projection * viewCoord;
    glm::vec3 ndc = glm::vec3(clipCoord)/clipCoord.w;
    glm::vec2 screen = glm::vec2((ndc.x+1)*(SCR_WIDTH/2),(ndc.y+1)*(SCR_HEIGHT/2));

    return screen;
}

bool ModifyVertex::searchVertex(float xpos, float ypos){
    Mesh* selectedMesh = Collection::GetInstance()->GetSelectedMesh();
    
    for(int i=0; i<selectedMesh->vertices.size(); i++){
        glm::vec2 screenMesh = coordinatelocalToScreen(selectedMesh->vertices[i].Position.x,selectedMesh->vertices[i].Position.y,selectedMesh->vertices[i].Position.z);
        if(abs(screenMesh.x- xpos)<=70 && abs(screenMesh.y- (SCR_HEIGHT-ypos))<=70){
            mSelectedIdx = i;
            return true;
        }
    }
    return false;
}