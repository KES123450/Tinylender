#include <vector>
#include "Widget.h"
#include <memory.h>

#pragma once

class Canvas{
    public:
        // 자식들의 draw() bVisible 체크해서 호출
        void rendering();
        void AddWidget(std::unique_ptr<Widget> w);

        //bVisible, 마우스 포인터 위치, 입력 여부에 따라  mChild의 buttonEvent 호출
        void handleButtonEvent();


    private:
        std::vector<std::unique_ptr<Widget>> mChild;
    

};