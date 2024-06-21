

#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <memory>
#include "IPressed.h"
#include "IPressedDown.h"
#include "IPressedUp.h"
#include "IMoved.h"
#include "constants.h"
#pragma once

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
        void AddMoved(IMoved* moved);

    private:
        std::vector<IPressed*> mPressed;
        std::vector<IPressedDown*> mPressedDown;
        std::vector<IPressedUp*> mPressedUp;
        std::vector<IMoved*> mMoved;


        float mLastX, mLastY, mDeltaX, mDeltaY;
        bool mLastLeftBtnPressed=false;
        bool mLastRightBtnPressed =false;

};
