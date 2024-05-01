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
        void OnPointerUp(float xpos, float ypos) override;


    private:
        std::vector<Widget*> mChild;
    

};

void Canvas::Rendering(){
    for(auto const& child : mChild){
        if(child->GetVisible()){
            child->Draw();
        }
    }
}


void Canvas::AddWidget(Widget* w){
    mChild.push_back(w);
}

void Canvas::OnPointerUp(float xpos, float ypos){
    float ndcX = (2*xpos/SCR_WIDTH)-1;
    float ndcY = 1-(2*ypos/SCR_HEIGHT);

    for(auto const& child:mChild){
        glm::vec3 pos = child -> GetPos();
        glm::vec2 size = child -> GetSize();
        glm::vec2 sizeHalf = glm::vec2(size.x/2,size.y/2);
        
        if(ndcX>=(pos.x-sizeHalf.x)
        &&ndcX<=(pos.x+sizeHalf.x)
        &&ndcY>=(pos.y-sizeHalf.y)
        &&ndcY<=(pos.y+sizeHalf.y)){
            if(child->getButtonCallback() != NULL)
                child->Callbtn();
        }
    }
}