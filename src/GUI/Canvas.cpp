/*

#include "Canvas.h"

void Canvas::rendering(){
    printf("%s","xxx");
    
    for(auto const& child : mChild){
        if(child->getVisible()){
            child->draw();
        }
    }
}


void Canvas::AddWidget(std::unique_ptr<Widget> w){
    mChild.push_back(std::move(w));
}

void Canvas::handleButtonEvent(){

} 

*/