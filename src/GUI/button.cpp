#include <glm/glm.hpp>
#include "button.h"
#include <glad/glad.h>

Button::Button(glm::vec3 buttonPos,float sizeX, float sizeY){
    mPushed=false;
    mButtonPos=buttonPos;
    mSizeX= sizeX;
    mSizeY = sizeY;
}

void Button::draw(){
    float halfX = mSizeX/2;
    float halfY = mSizeY/2;

    float left=mButtonPos.x-halfX;
    float right = mButtonPos.x+halfX;
    float top = mButtonPos.y + halfY;
    float bottom = mButtonPos.y - halfY;

    glBegin(GL_QUADS);
    glVertex3d(left,bottom,0.0f);
    glVertex3d(left,top,0.0f);
    glVertex3d(right,bottom,0.0f);
    glVertex3d(left,bottom,0.0f);

    glEnd();
}

void Button::setbuttonCallback(std::function<void(GLFWwindow* window, double xpos, double ypos)>& callback){
    mbuttonCallback = callback;
}


