#pragma once

class IState{
    public:
        virtual ~IState() {};
        virtual void Handle() =0;
};