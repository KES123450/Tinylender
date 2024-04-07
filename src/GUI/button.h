#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Widget.h"

#pragma once

class Button:public Widget{
    public:
        Button(glm::vec3 buttonPos,float sizeX, float sizeY);

        void setbuttonCallback(std::function<void(GLFWwindow* window, double xpos, double ypos)>& callback) override;
        void draw() override;
        bool getVisible() override;
        
        std::function<void(GLFWwindow* window, double xpos, double ypos)>& getButtonCallback();
        bool pushed() const {return mPushed;}
        void setPushed(bool pushed) {mPushed=pushed;}
        

    private:
        glm::vec3 mButtonPos;
        float mSizeX,mSizeY;
        bool mPushed;
};