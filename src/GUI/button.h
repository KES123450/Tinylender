#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <stb_image.h>
#include <iostream>
#include "Widget.h"
#include "../constants.h"
#include "../Shader/Shader.h"

#pragma once

class Button:public Widget{
    public:
        Button(glm::vec3 buttonPos,float sizeX, float sizeY, const char *texPath, eImageType imageType);

        void Draw() override;
        
        bool GetPushed() const {return mPushed;}
        void Pushed();
        void SetTexture(const char *texPath,eImageType imageType);
        

    private:
        Shader UIShader;
        unsigned int mVBO;
        unsigned int mVAO;
        unsigned int mEBO;
        unsigned int mTexture;
        int mWidth, mHeight, mMinimaps;
        float mVertexArray[20];
        glm::vec4 mColor= glm::vec4(1.0f,1.0f,1.0f,1.0f);
        unsigned int mIndices[6]={
            0,1,2,
            2,1,3
        };
};

Button::Button(glm::vec3 buttonPos,float sizeX, float sizeY,const char *texPath, eImageType imageType)
: UIShader("Shader/UIVertexShader.glsl", "Shader/UIFragmentShader.glsl"){
    mPushed=false;
    mSizeX =sizeX;
    mSizeY=sizeY;
    mPos=buttonPos;

    float halfX = mSizeX/2;
    float halfY = mSizeY/2;


    glm::vec3 vertex[4];
    vertex[0] = glm::vec3(buttonPos.x-halfX,buttonPos.y+halfY,0.0f);
    vertex[1] = glm::vec3(buttonPos.x-halfX,buttonPos.y-halfY,0.0f);
    vertex[2] = glm::vec3(buttonPos.x+halfX,buttonPos.y+halfY,0.0f);
    vertex[3] = glm::vec3(buttonPos.x+halfX,buttonPos.y-halfY,0.0f);

    glm::vec2 texCoord[4];
    texCoord[0] = glm::vec2(0.0f,1.0f);
    texCoord[1] = glm::vec2(0.0f,0.0f);
    texCoord[2] = glm::vec2(1.0f,1.0f);
    texCoord[3] = glm::vec2(1.0f,0.0f);

    for(int i=0;i<4;i++){
        mVertexArray[i*5+0] = vertex[i].x;
        mVertexArray[i*5+1] = vertex[i].y;
        mVertexArray[i*5+2] = vertex[i].z;
        mVertexArray[i*5+3] = texCoord[i].x;
        mVertexArray[i*5+4] = texCoord[i].y;

    }

    glGenBuffers(1,&mVBO);
    glGenVertexArrays(1,&mVAO);
    glGenBuffers(1,&mEBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER,mVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(mVertexArray),mVertexArray,GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(mIndices),mIndices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);  
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenTextures(1,&mTexture);
    SetTexture(texPath,imageType);

}

void Button::SetTexture(const char *texPath,eImageType imageType){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,mTexture);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    stbi_set_flip_vertically_on_load(true); 
    unsigned char *data = stbi_load(texPath,&mWidth,&mHeight,&mMinimaps,0);


    if(data){
        switch(imageType){
            case JPG:
                glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,mWidth,mHeight,0,GL_RGB,GL_UNSIGNED_BYTE,data);
                glGenerateMipmap(GL_TEXTURE_2D);
                break;
            
            case PNG:
                glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,mWidth,mHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
                glGenerateMipmap(GL_TEXTURE_2D);
                break;
        }
    }
    else{
        printf("%s","textureFail");
    }

    stbi_image_free(data);
    UIShader.use();
    glUniform1i(glGetUniformLocation(UIShader.ID, "ourTexture"), 0);
}

void Button::Draw(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,mTexture);
    UIShader.use();
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}


void Button::Pushed(){
    if(mPushed==true){
        mPushed=false;
    }
    else{
        mPushed=true;
    }

}