#pragma once


class IPressedUp{
    
    public:
        virtual ~IPressedUp() {};
        virtual void OnPointerUp(float xpos, float ypos) = 0;
};