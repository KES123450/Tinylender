#include "constants.h"
#include "IState.h"

#pragma once

class Context{
    public:
        Context(IState* layerState, IState* dotState, IState* lineState, IState* surfaceState);
        void Transition(eUIState state);
        void HandleState();
        eUIState GetState() const {return mState;}

    private:
        eUIState mState;
        IState* mCurrentState=NULL;
        IState* mLayerState;
        IState* mDotState;
        IState* mLineState;
        IState* mSurfaceState;

};

Context::Context(IState* layerState, IState* dotState, IState* lineState, IState* surfaceState){
    mLayerState=layerState;
    mDotState =dotState;
    mLineState =lineState;
    mSurfaceState =surfaceState;
}

void Context::Transition(eUIState state)
{

    if(mState!=state&&mCurrentState!=NULL){
        mCurrentState->HandleOut();
    }

    switch (state)
    {
        case EMPTY:
            mState=state;
            mCurrentState = NULL;
            break;

        case LAYER:
            mState=state;
            mCurrentState = mLayerState;
            break;

        case DOT:
            mState=state;
            mCurrentState = mDotState;
            break;

        case LINE:
            mState=state;
            mCurrentState = mLineState;
            break;

        case SURFACE:
            mState=state;
            mCurrentState = mSurfaceState;
            break;
        
        default:
            break;
    }
}

void Context::HandleState(){
    if(mCurrentState!=NULL)
         mCurrentState->Handle();
}