

#include "constants.h"
#include "IState.h"

#pragma once

class Context
{
public:
    Context(IState *layerState, IState *dotState, IState *lineState, IState *surfaceState);
    void Transition(eUIState state);
    void HandleState();
    eUIState GetState() const { return mState; }

private:
    eUIState mState;
    IState *mCurrentState = nullptr;
    IState *mLayerState;
    IState *mDotState;
    IState *mLineState;
    IState *mSurfaceState;
};


