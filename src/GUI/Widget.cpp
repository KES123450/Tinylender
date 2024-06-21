#include "Widget.h"


void Widget::Callbtn(){
    mbuttonCallback(0.0f,0.0f);
}

void Widget::SetbuttonCallback(std::function<void(double xpos, double ypos)> callback){
    mbuttonCallback = callback;
}
Widget::~Widget() {
    // 가상 소멸자 정의
}

