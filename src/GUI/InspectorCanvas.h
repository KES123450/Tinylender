#pragma once
#include <glm/glm.hpp>
#include <array>
#include <tuple>
#include <string>
#include "Widget.h"
#include "TextBox.h"
#include "button.h"
#include "../Layer.h"
#include "../ShapeLayer.h"
#include "../LightLayer.h"
#include "../InputEventSystem.h"
#include "../IPressedUp.h"
#include "Panel.h"

class InspectorCanvas : public IPressedUp
{
public:
    InspectorCanvas(Layer *rootLayer);
    void Rendering();
    void SetInspector(Layer *layer);
    void AddWidget(Widget *w);
    void OnPointerUp(float xpos, float ypos, float xdelta, float ydelta) override;
    void SetColor(glm::vec3 color);

private:
    Layer *mSelectedLayer;
    std::vector<Widget *> mChild;
    TextBox *mPositionTextBoxX, *mPositionTextBoxY, *mPositionTextBoxZ, *mRotationTextBoxX, *mRotationTextBoxY, *mRotationTextBoxZ, *mScaleTextBoxX, *mScaleTextBoxY, *mScaleTextBoxZ;
    std::array<Button *, 21> mButtons = {nullptr};
    Panel *mInspectorPanel;

    TextBox *t;

    void setPositionX(std::string str);
    void setPositionY(std::string str);
    void setPositionZ(std::string str);
    void setRotationX(std::string str);
    void setRotationY(std::string str);
    void setRotationZ(std::string str);
};