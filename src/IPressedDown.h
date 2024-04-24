#pragma once


class IPressedDown{
    
    public:
        virtual ~IPressedDown() {};
        virtual void OnPointerDown(float xpos, float ypos) =0;
};