//#define STB_IMAGE_IMPLEMENTATION


#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include "../stb_image.h"
#include<iostream>
#include <glm/glm.hpp>

#pragma once

class Widget{
    public:
        virtual ~Widget();
        virtual void Draw()=0;

        bool GetVisible() const {return bVisible;}
        void SetbuttonCallback(std::function<void(double xpos, double ypos)> callback);
        std::function<void(double xpos, double ypos)> getButtonCallback() const {return mbuttonCallback;}
        
        glm::vec3 GetPos() const {return mPos;}
        void SetPos(glm::vec3 offset);
        glm::vec2 GetSize() const {return glm::vec2(mSizeX,mSizeY);}
        void Callbtn();



    protected:
        bool mPushed=false;
        glm::vec3 mPos;
        float mSizeX;
        float mSizeY;
        bool bVisible=true;
        std::function<void(double xpos, double ypos)> mbuttonCallback = NULL;

};
