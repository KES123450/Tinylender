#include<iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#pragma once

class Widget{
    public:
        virtual ~Widget();
        virtual void setbuttonCallback(std::function<void(GLFWwindow* window, double xpos, double ypos)>& callback)=0;
        virtual void draw()=0;
        virtual bool getVisible() const =0;

        glm::vec3 GetPos() const {return mPos;}
        glm::vec2 GetSize() const {return glm::vec2(mSizeX,mSizeY);}



    protected:
        bool mPushed;
        glm::vec3 mPos;
        float mSizeX;
        float mSizeY;
        bool bVisible=true;
        std::function<void(GLFWwindow* window, double xpos, double ypos)> mbuttonCallback;

};

Widget::~Widget() {
    // 가상 소멸자 정의
}