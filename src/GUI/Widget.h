#include<iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#pragma once

class Widget{
    public:
        virtual ~Widget();
        virtual void Draw()=0;
        virtual bool GetVisible() const =0;

        void SetbuttonCallback(std::function<void(double xpos, double ypos)> callback);
        std::function<void(GLFWwindow* window, double xpos, double ypos)>& getButtonCallback();
        
        glm::vec3 GetPos() const {return mPos;}
        glm::vec2 GetSize() const {return glm::vec2(mSizeX,mSizeY);}
        void Callbtn();



    protected:
        bool mPushed=false;
        glm::vec3 mPos;
        float mSizeX;
        float mSizeY;
        bool bVisible=true;
        std::function<void(double xpos, double ypos)> mbuttonCallback;

};

void Widget::Callbtn(){
    mbuttonCallback(0.0f,0.0f);
}

void Widget::SetbuttonCallback(std::function<void(double xpos, double ypos)> callback){
    mbuttonCallback = callback;
}
Widget::~Widget() {
    // 가상 소멸자 정의
}