#pragma once


class IPressedUp{
    public:
        virtual ~IPressedUp() {};
        virtual void OnPointerUp(float xpos, float ypos,float xdelta,float ydelta) = 0;
};