#pragma once


class IPressed{
    public:
        virtual ~IPressed() {};
        virtual void OnPointer(float xpos, float ypos) = 0;
};

