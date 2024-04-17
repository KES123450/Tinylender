#include <vector>
#include "Widget.h"
#include "button.h"
#include <memory>

#pragma once

class Canvas{
    public:
        // 자식들의 draw() bVisible 체크해서 호출
        void rendering();
        void AddWidget(std::unique_ptr<Button> w);

        //bVisible, 마우스 포인터 위치, 입력 여부에 따라  mChild의 buttonEvent 호출
        void handleButtonEvent();


    private:
        std::vector<std::unique_ptr<Widget> > mChild;
    

};

void Canvas::rendering(){
    printf("%s","xxx");
    
    for(auto const& child : mChild){
        if(child->getVisible()){
            child->draw();
        }
    }
    
}


void Canvas::AddWidget(std::unique_ptr<Button> w){
    mChild.push_back(std::move(w));
}

void Canvas::handleButtonEvent(){

}