#include "constants.h"

#pragma once

class Context{
    public:
        void Transition(eUIState state);
        eUIState GetState() const {return mState};

    private:
        eUIState mState;
}

Context::Transition(eUIState state){
    
}