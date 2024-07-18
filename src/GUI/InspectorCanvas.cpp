#include "InspectorCanvas.h"

InspectorCanvas::InspectorCanvas()
{
    mPositionTextBoxX= new TextBox(glm::vec3(0.8196939454424483f,0.7682926829268293f,0.0f),0.0385894876912841f,0.02926829268292683f,"123.3",0.3f,false);

}

void InspectorCanvas::AddWidget(Widget* w)
{
    mChild.push_back(w);
}

void InspectorCanvas::SetPositionX(std::string str){
    mSelectedLayer->position.x = std::stoi(str);
}

void InspectorCanvas::SetInspector(Layer *layer)
{
    mSelectedLayer = layer;
    mPositionTextBoxX->SetText(std::to_string(layer->position.x));
    mPositionTextBoxY->SetText(std::to_string(layer->position.y));
    mPositionTextBoxZ->SetText(std::to_string(layer->position.z));

    mRotateTextBoxX->SetText(std::to_string(layer->rotation.x));
    mRotateTextBoxY->SetText(std::to_string(layer->rotation.y));
    mRotateTextBoxZ->SetText(std::to_string(layer->rotation.z));

    mScaleTextBoxX->SetText(std::to_string(layer->scale.x));
    mScaleTextBoxY->SetText(std::to_string(layer->scale.y));
    mScaleTextBoxZ->SetText(std::to_string(layer->scale.z));
}



