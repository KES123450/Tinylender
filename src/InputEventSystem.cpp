#include "InputEventSystem.h"

InputEventSystem* InputEventSystem::instance = nullptr;

InputEventSystem* InputEventSystem::GetInstance(){
    if(instance==NULL)
        instance = new InputEventSystem();
    return instance;
}

void InputEventSystem::AddPressed(IPressed* pressed){
    mPressed.push_back(pressed);
}

void InputEventSystem::AddPressedDown(IPressedDown* pressedDown){
    mPressedDown.push_back(pressedDown);
}

void InputEventSystem::AddPressedUp(IPressedUp* pressedUp){
    mPressedUp.push_back(pressedUp);
}

void InputEventSystem::AddMoved(IMoved* moved){
    mMoved.push_back(moved);
}

void InputEventSystem::AddScrolled(IScrolled* scrolled){
    mScrolled.push_back(scrolled);
}

void InputEventSystem::AddKeyDown(IKeyDown* keyDown){
    mKeyDown.push_back(keyDown);
}

void InputEventSystem::HandleInputPos(double xpos, double ypos){
    mDeltaX= xpos-mLastX;
    mDeltaY= ypos-mLastY;
    mLastX = xpos;
    mLastY= ypos;


    if(mLastLeftBtnPressed==true){

        for(auto const& child : mPressed){
            child->OnPointer(mLastX,mLastY,mDeltaX,mDeltaY);
        }

        mLastLeftBtnPressed=true;
    }

    for(auto const& child: mMoved){
        child->OnMove(mLastX,mLastY,mDeltaX,mDeltaY);
    }
}


void InputEventSystem::HandleInputEvent(int button, int action){

    if(mLastLeftBtnPressed==false && button==GLFW_MOUSE_BUTTON_LEFT && action==GLFW_PRESS){


        for(auto const& child : mPressedDown){
            child->OnPointerDown(mLastX,mLastY,mDeltaX,mDeltaY);
        }

        mLastLeftBtnPressed=true;
        return;
    }


    if(mLastLeftBtnPressed==true && button==GLFW_MOUSE_BUTTON_LEFT && action==GLFW_RELEASE){

        for(auto const& child : mPressedUp){
            child->OnPointerUp(mLastX,mLastY,mDeltaX,mDeltaY);
        }

        mLastLeftBtnPressed=false;
        return;
    }

}

void InputEventSystem::HandleScrollEvent(double xoffset, double yoffset){
    for(IScrolled* child : mScrolled){
        child->OnScroll(xoffset, yoffset);
    }

}

void InputEventSystem::HandleKeyEvent(int key, int action){
    if(key == GLFW_KEY_0 && action == GLFW_PRESS){
        for(IKeyDown* child : mKeyDown){
            child->GeyKeyDown("0");
        }
        return;
    }

    if(key == GLFW_KEY_1 && action == GLFW_PRESS){
        for(IKeyDown* child : mKeyDown){
            child->GeyKeyDown("1");
        }
        return;
    }

    if(key == GLFW_KEY_2 && action == GLFW_PRESS){
        for(IKeyDown* child : mKeyDown){
            child->GeyKeyDown("2");
        }
        return;
    }
    
    if(key == GLFW_KEY_3 && action == GLFW_PRESS){
        for(IKeyDown* child : mKeyDown){
            child->GeyKeyDown("3");
        }
        return;
    }
    
        if(key == GLFW_KEY_4 && action == GLFW_PRESS){
        for(IKeyDown* child : mKeyDown){
            child->GeyKeyDown("4");
        }
        return;
    }
    
    if(key == GLFW_KEY_5 && action == GLFW_PRESS){
        for(IKeyDown* child : mKeyDown){
            child->GeyKeyDown("5");
        }
        return;
    }
    
    if(key == GLFW_KEY_6 && action == GLFW_PRESS){
        for(IKeyDown* child : mKeyDown){
            child->GeyKeyDown("6");
        }
        return;
    }
    
    if(key == GLFW_KEY_7 && action == GLFW_PRESS){
        for(IKeyDown* child : mKeyDown){
            child->GeyKeyDown("7");
        }
        return;
    }
    
        if(key == GLFW_KEY_8 && action == GLFW_PRESS){
        for(IKeyDown* child : mKeyDown){
            child->GeyKeyDown("8");
        }
        return;
    }
    
        if(key == GLFW_KEY_9 && action == GLFW_PRESS){
        for(IKeyDown* child : mKeyDown){
            child->GeyKeyDown("9");
        }
        return;
    }
    
        
        
}
