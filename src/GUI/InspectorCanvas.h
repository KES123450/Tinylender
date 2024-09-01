#pragma once
#include <glm/glm.hpp>
#include "Widget.h"
#include "TextBox.h"
#include "../Layer.h"
#include "../ShapeLayer.h"
#include "../InputEventSystem.h"
#include "Panel.h"

class InspectorCanvas{
    public:
        InspectorCanvas();
        void Rendering();
        void SetInspector(Layer* layer);
        void AddWidget(Widget* w);

    
    private:
        Layer* mSelectedLayer;
        std::vector<Widget*> mChild;
        TextBox *mPositionTextBoxX, *mPositionTextBoxY, *mPositionTextBoxZ
        ,*mRotationTextBoxX, *mRotationTextBoxY, *mRotationTextBoxZ
        ,*mScaleTextBoxX, *mScaleTextBoxY, *mScaleTextBoxZ;
        Panel *mInspectorPanel;

        TextBox* t;

        void setPositionX(std::string str);
        void setPositionY(std::string str);
        void setPositionZ(std::string str);
        void setRotationX(std::string str);
        void setRotationY(std::string str);
        void setRotationZ(std::string str);
        void SetColor(glm::vec3 color);
        
};