
#include <vector>
#include <glm/glm.hpp>
#include "Widget.h"
#include "button.h"
#include <memory>
#include "../constants.h"
#include "../IPressedUp.h"

#pragma once

class Canvas : public IPressedUp{
    public:
        // 자식들의 draw() bVisible 체크해서 호출
        void Rendering();
        void AddWidget(Widget* w);
        void OnPointerUp(float xpos, float ypos,float xdelta,float ydelta) override;

    private:
        std::vector<Widget*> mChild;
    

};

