#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "Widget.h"

#pragma once

class Button:public Widget{
    public:
        Button(glm::vec3 buttonPos,float sizeX, float sizeY);

        void inputButtonEvent(GLFWwindow* window, double xpos, double ypos);
        void draw();
        bool pushed() const {return mPushed;}
        void setPushed(bool pushed) {mPushed=pushed;}
        

    private:
        glm::vec3 mButtonPos;
        float mSizeX,mSizeY;
        bool mPushed;
};