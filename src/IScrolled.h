#pragma once

class IScrolled{
    public:
        virtual ~IScrolled() {};
        virtual void OnScroll(float xoffset, float yoffset)=0;

};