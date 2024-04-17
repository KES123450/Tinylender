#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Widget.h"
#include "../Shader/Shader.h"

#pragma once

class Button:public Widget{
    public:
        Button(glm::vec3 buttonPos,float sizeX, float sizeY);

        void setbuttonCallback(std::function<void(GLFWwindow* window, double xpos, double ypos)>& callback) override;
        void draw() override;
        bool getVisible() const override{return bVisible;}
        
        std::function<void(GLFWwindow* window, double xpos, double ypos)>& getButtonCallback();
        bool pushed() const {return mPushed;}
        void setPushed(bool pushed) {mPushed=pushed;}
        

    private:
        Shader UIShader;
        glm::vec3 mButtonPos;
        float mSizeX,mSizeY;
        bool mPushed;
        unsigned int mVBO;
        unsigned int mVAO;
        unsigned int mEBO;
        float mVertexArray[12];
        unsigned int mIndices[6]={
            0,1,2,
            2,1,3
        };
};

Button::Button(glm::vec3 buttonPos,float sizeX, float sizeY)
: UIShader("src/Shader/UIVertexShader.glsl", "src/Shader/UIFragmentShader.glsl"){
    mPushed=false;
    float halfX = mSizeX/2;
    float halfY = mSizeY/2;

    glm::vec3 v1 = glm::vec3(buttonPos.x-halfX,buttonPos.y+halfY,0.0f);
    glm::vec3 v2 = glm::vec3(buttonPos.x-halfX,buttonPos.y-halfY,0.0f);
    glm::vec3 v3 = glm::vec3(buttonPos.x+halfX,buttonPos.y+halfY,0.0f);
    glm::vec3 v4 = glm::vec3(buttonPos.x+halfX,buttonPos.y-halfY,0.0f);

    for(int i=0;i<4;i++){
        mVertexArray[i*3+0] = v1.x;
        mVertexArray[i*3+1] = v1.y;
        mVertexArray[i*3+2] = v1.z;
    }

    glGenBuffers(1,&mVBO);
    glGenVertexArrays(1,&mVAO);
    glGenBuffers(1,&mEBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER,mVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(mVertexArray),mVertexArray,GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(mIndices),mIndices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);  

    mButtonPos=buttonPos;
    mSizeX= sizeX;
    mSizeY = sizeY;
}

void Button::draw(){
    printf("%s","draw");
    UIShader.use();
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}

void Button::setbuttonCallback(std::function<void(GLFWwindow* window, double xpos, double ypos)>& callback){
    mbuttonCallback = callback;
}