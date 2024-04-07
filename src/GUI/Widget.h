#include<iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#pragma once

class Widget{
    public:
        virtual void setbuttonCallback(std::function<void(GLFWwindow* window, double xpos, double ypos)>& callback)=0;
        virtual void draw()=0;
        virtual bool getVisible()=0;


    protected:
        bool bVisible;
        std::function<void(GLFWwindow* window, double xpos, double ypos)> mbuttonCallback;

};