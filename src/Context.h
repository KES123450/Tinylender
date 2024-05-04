#include "constants.h"
#include "IState.h"

#pragma once

class Context{
    public:
        Context(IState layerState, IState dotState, IState lineState, IState surfaceState);
        void Transition(eUIState state);
        eUIState GetState() const {return mState};

    private:
        eUIState mState;
        IState mLayerState,mDotState,mLineState,mSurfaceState;
}

Context::Transition(eUIState state){
    
}