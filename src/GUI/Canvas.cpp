#include "Canvas.h"

void Canvas::rendering(){
    for(auto const& child : mChild){
        if(child->getVisible()){
            child->draw();
        }
    }

};

void Canvas::AddWidget(std::unique_ptr<Widget> w){
    mChild.push_back(w);
}
