#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <memory>
#include "IPressed.h"
#include "IPressedDown.h"
#include "IPressedUp.h"

#pragma once

enum eInputState{
    Pressed,
    Released,
    PressedAndReleased,
    NotChanged
};


class InputEventSystem{
    public:
        eInputState inputState;

        // 마우스 움질일 때마다 감지해서 inputPosition 변경
        void HandleInputPos(double xpos, double ypos);
        //현재 있는 canvas에 접근하여 지금 인풋 위치 범위에 있는 UI의 callback함수 호출
        void HandleInputEvent(int button, int action);

        void AddPressed(IPressed* pressed);
        void AddPressedDown(IPressedDown* pressedDown);
        void AddPressedUp(IPressedUp* pressedUp);


    private:
        std::vector<IPressed*> mPressed;
        std::vector<IPressedDown*> mPressedDown;
        std::vector<IPressedUp*> mPressedUp;

        float mLastX, mLastY;
        bool mLastLeftBtnPressed=false;
        bool mLastRightBtnPressed =false;

        
};

void InputEventSystem::AddPressed(IPressed* pressed){
    mPressed.push_back(pressed);
}

void InputEventSystem::AddPressedDown(IPressedDown* pressedDown){
    mPressedDown.push_back(pressedDown);
}

void InputEventSystem::AddPressedUp(IPressedUp* pressedUp){
    mPressedUp.push_back(pressedUp);
}

void InputEventSystem::HandleInputPos(double xpos, double ypos){
    mLastX = xpos;
    mLastY= ypos;
}


void InputEventSystem::HandleInputEvent(int button, int action){

    if(mLastLeftBtnPressed==false && button==GLFW_MOUSE_BUTTON_LEFT && action==GLFW_PRESS){
        for(auto const& child : mPressedDown){
            child->OnPointerDown(mLastX,mLastY);
        }

        mLastLeftBtnPressed=true;
        return;
    }

    if(mLastLeftBtnPressed==true && button==GLFW_MOUSE_BUTTON_LEFT && action==GLFW_PRESS){
        for(auto const& child : mPressed){
            child->OnPointer(mLastX,mLastY);
        }


        mLastLeftBtnPressed=true;
        return;
    }

    if(mLastLeftBtnPressed==true && button==GLFW_MOUSE_BUTTON_LEFT && action==GLFW_RELEASE){
        for(auto const& child : mPressedUp){
            child->OnPointerUp(mLastX,mLastY);
        }

        mLastLeftBtnPressed=false;
        return;
    }

}

