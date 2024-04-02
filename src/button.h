#include <glm/glm.hpp>


#pragma once

class Button{
    public:
        Button(glm::vec3 buttonPos,float sizeX, float sizeY);

        bool pushed() const {return mPushed;}
        void setPushed(bool pushed) {mPushed=pushed;}
        void mouseButtonEvent(GLFWwindow* window, double xpos, double ypos);
        void draw();

    private:
        glm::vec3 mButtonPos;
        float mSizeX,mSizeY;
        bool mPushed;
};