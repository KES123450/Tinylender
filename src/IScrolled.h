#pragma once

class IScrolled{
    public:
        virtual ~IScrolled() {};
        virtual void OnScroll(double xoffset, double yoffset)=0;

}