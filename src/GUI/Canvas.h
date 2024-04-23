#include <vector>
#include <glm/glm.hpp>
#include "Widget.h"
#include "button.h"
#include <memory>

#pragma once

class Canvas{
    public:
        // 자식들의 draw() bVisible 체크해서 호출
        void rendering();
        void AddWidget(std::unique_ptr<Widget> w);

        //bVisible, 마우스 포인터 위치, 입력 여부에 따라  mChild의 buttonEvent 호출
        void handleInputEvent(double xpos, double ypos);


    private:
        std::vector<std::unique_ptr<Widget> > mChild;
    

};

void Canvas::rendering(){
    
    for(auto const& child : mChild){
        if(child->getVisible()){
            child->draw();
        }
    }
    
}


void Canvas::AddWidget(std::unique_ptr<Widget> w){
    mChild.push_back(std::move(w));
}

void Canvas::handleInputEvent(double xpos, double ypos){
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
            
        }


    }

}