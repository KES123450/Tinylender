#pragma once

class IMoved{   
    public:
        virtual ~IMoved() {};
        virtual void OnMove(float xpos, float ypos,float xdelta,float ydelta) =0;

};