#pragma once


class IPressedDown{
    
    public:
        virtual ~IPressedDown() {};
        virtual void OnPointerDown(float xpos, float ypos,float xdelta,float ydelta) =0;
};