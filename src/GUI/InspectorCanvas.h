#pragma once

#include "Widget.h"
#include "TextBox.h"
#include "../Layer.h"

class InspectorCanvas{
    public:
        InspectorCanvas();
        void Rendering();
        void SetInspector(Layer* layer);
        void AddWidget(Widget* w);
        void SetPositionX(std::string str);
    
    private:
        Layer* mSelectedLayer;
        std::vector<Widget*> mChild;
        TextBox *mPositionTextBoxX, *mPositionTextBoxY, *mPositionTextBoxZ
        ,*mRotateTextBoxX, *mRotateTextBoxY, *mRotateTextBoxZ
        ,*mScaleTextBoxX, *mScaleTextBoxY, *mScaleTextBoxZ;

};