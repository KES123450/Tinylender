#pragma once

class IPressed
{
public:
    virtual ~IPressed() {};
    virtual void OnPointer(float xpos, float ypos, float xdelta, float ydelta) = 0;
};


