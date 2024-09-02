#include "Widget.h"

void Widget::SetPos(glm::vec3 offset){
    mPos+=offset;
}

Widget::~Widget() {
    // 가상 소멸자 정의
}

