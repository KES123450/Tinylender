#pragma once
#include <string>

class IKeyDown{
    public:
        virtual ~IKeyDown() {};
        virtual void GeyKeyDown(std::string str) =0;
};