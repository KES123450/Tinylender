#include "Context.h"


Context::Context(IState* layerState, IState* dotState, IState* lineState, IState* surfaceState){
    mLayerState=layerState;
    mDotState =dotState;
    mLineState =lineState;
    mSurfaceState =surfaceState;
}

void Context::Transition(eUIState state)
{

    if(mState!=state&&mCurrentState!=nullptr){
        mCurrentState->HandleOut();
    }

    switch (state)
    {
        case eUIState::EMPTY:
            mState=state;
            mCurrentState = nullptr;
            break;

        case eUIState::LAYER:
            mState=state;
            mCurrentState = mLayerState;
            break;

        case eUIState::DOT:
            mState=state;
            mCurrentState = mDotState;
            break;

        case eUIState::LINE:
            mState=state;
            mCurrentState = mLineState;
            break;

        case eUIState::SURFACE:
            mState=state;
            mCurrentState = mSurfaceState;
            break;
        
        default:
            break;
    }
}

void Context::HandleState(){
    if(mCurrentState!=nullptr)
        mCurrentState->Handle();
}

