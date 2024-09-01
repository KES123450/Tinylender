#include "InspectorCanvas.h"

InspectorCanvas::InspectorCanvas()
{
    mInspectorPanel = new Panel(glm::vec3(0.8443113772455091f, -0.06008536585365842f, 0.0f), 0.31137724550898205f, 1.879829268292683, "resource/inspector.png", eImageType::PNG);
    AddWidget(mInspectorPanel);

    mPositionTextBoxX = new TextBox(glm::vec3(0.8196939454424483f, 0.7682926829268293f, 0.0f), 0.0385894876912841f, 0.02926829268292683f, "1", 0.3f, glm::vec3(0.85098039215f, 0.85098039215f, 0.85098039215f), false);
    InputEventSystem::GetInstance()->AddPressedDown(mPositionTextBoxX);
    InputEventSystem::GetInstance()->AddKeyDown(mPositionTextBoxX);
    mPositionTextBoxX->SetEventCallback([this](std::string str)
                                        { setPositionX(str); });
    AddWidget(mPositionTextBoxX);

    mPositionTextBoxY = new TextBox(glm::vec3(0.8875582168995342f, 0.7682926829268293f, 0.0f), 0.0385894876912841f, 0.02926829268292683f, "1", 0.3f, glm::vec3(0.85098039215f, 0.85098039215f, 0.85098039215f), false);
    InputEventSystem::GetInstance()->AddPressedDown(mPositionTextBoxY);
    InputEventSystem::GetInstance()->AddKeyDown(mPositionTextBoxY);
    mPositionTextBoxY->SetEventCallback([this](std::string str)
                                        { setPositionY(str); });
    AddWidget(mPositionTextBoxY);

    mPositionTextBoxZ = new TextBox(glm::vec3(0.95542248835662f, 0.7682926829268293f, 0.0f), 0.0385894876912841f, 0.02926829268292683f, "1", 0.3f, glm::vec3(0.85098039215f, 0.85098039215f, 0.85098039215f), false);
    InputEventSystem::GetInstance()->AddPressedDown(mPositionTextBoxZ);
    InputEventSystem::GetInstance()->AddKeyDown(mPositionTextBoxZ);
    mPositionTextBoxY->SetEventCallback([this](std::string str)
                                        { setPositionZ(str); });
    AddWidget(mPositionTextBoxZ);

    mRotationTextBoxX = new TextBox(glm::vec3(0.8196939454424483f, 0.7012195121951219f, 0.0f), 0.0385894876912841f, 0.02926829268292683f, "1", 0.3f, glm::vec3(0.85098039215f, 0.85098039215f, 0.85098039215f), false);
    InputEventSystem::GetInstance()->AddPressedDown(mRotationTextBoxX);
    InputEventSystem::GetInstance()->AddKeyDown(mRotationTextBoxX);
    mRotationTextBoxX->SetEventCallback([this](std::string str)
                                        { setRotationX(str); });
    AddWidget(mRotationTextBoxX);

    mRotationTextBoxY = new TextBox(glm::vec3(0.8875582168995342f, 0.7012195121951219f, 0.0f), 0.0385894876912841f, 0.02926829268292683f, "1", 0.3f, glm::vec3(0.85098039215f, 0.85098039215f, 0.85098039215f), false);
    InputEventSystem::GetInstance()->AddPressedDown(mRotationTextBoxY);
    InputEventSystem::GetInstance()->AddKeyDown(mRotationTextBoxY);
    mRotationTextBoxY->SetEventCallback([this](std::string str)
                                        { setRotationY(str); });
    AddWidget(mRotationTextBoxY);

    mRotationTextBoxZ = new TextBox(glm::vec3(0.95542248835662f, 0.7012195121951219f, 0.0f), 0.0385894876912841f, 0.02926829268292683f, "1", 0.3f, glm::vec3(0.85098039215f, 0.85098039215f, 0.85098039215f), false);
    InputEventSystem::GetInstance()->AddPressedDown(mRotationTextBoxZ);
    InputEventSystem::GetInstance()->AddKeyDown(mRotationTextBoxZ);
    mRotationTextBoxZ->SetEventCallback([this](std::string str)
                                        { setRotationZ(str); });
    AddWidget(mRotationTextBoxZ);
}

void InspectorCanvas::AddWidget(Widget *w)
{
    mChild.push_back(w);
}

void InspectorCanvas::setPositionX(std::string str)
{
    if (!mSelectedLayer)
        return;
    glm::vec3 nowPosition = mSelectedLayer->GetPosition();
    glm::vec3 newPosition;
    if (!str.empty())
    {
        newPosition = glm::vec3(std::stof(str), nowPosition.y, nowPosition.z);
    }
    else
    {
        newPosition = nowPosition;
    }

    switch (mSelectedLayer->layerType)
    {
    case eLayerType::SHAPE:
        static_cast<ShapeLayer *>(mSelectedLayer)->SetPosition(newPosition);
        break;

    default:
        break;
    }
}

void InspectorCanvas::setPositionY(std::string str)
{
    if (!mSelectedLayer)
        return;
    glm::vec3 nowPosition = mSelectedLayer->GetPosition();
    glm::vec3 newPosition;
    if (!str.empty())
    {
        newPosition = glm::vec3(nowPosition.x, std::stof(str), nowPosition.z);
    }
    else
    {
        newPosition = nowPosition;
    }

    switch (mSelectedLayer->layerType)
    {
    case eLayerType::SHAPE:
        static_cast<ShapeLayer *>(mSelectedLayer)->SetPosition(newPosition);
        break;

    default:
        break;
    }
}

void InspectorCanvas::setPositionZ(std::string str)
{
    if (!mSelectedLayer)
        return;
    glm::vec3 nowPosition = mSelectedLayer->GetPosition();
    glm::vec3 newPosition;
    if (!str.empty())
    {
        newPosition = glm::vec3(nowPosition.x, nowPosition.y, std::stof(str));
    }
    else
    {
        newPosition = nowPosition;
    }

    switch (mSelectedLayer->layerType)
    {
    case eLayerType::SHAPE:
        static_cast<ShapeLayer *>(mSelectedLayer)->SetPosition(newPosition);
        break;

    default:
        break;
    }
}

void InspectorCanvas::setRotationX(std::string str)
{
    if (!mSelectedLayer)
        return;

    glm::vec3 nowRotation = mSelectedLayer->GetRotation();
    glm::vec3 newRotation;
    if (!str.empty())
    {
        newRotation = glm::vec3(std::stof(str), nowRotation.y, nowRotation.z);
    }
    else
    {
        newRotation = nowRotation;
    }

    switch (mSelectedLayer->layerType)
    {
    case eLayerType::SHAPE:
        static_cast<ShapeLayer *>(mSelectedLayer)->SetRotation(newRotation);
        break;

    default:
        break;
    }
}

void InspectorCanvas::setRotationY(std::string str)
{
    if (!mSelectedLayer)
        return;

    glm::vec3 nowRotation = mSelectedLayer->GetRotation();
    glm::vec3 newRotation;
    if (!str.empty())
    {
        newRotation = glm::vec3(nowRotation.x, std::stof(str), nowRotation.z);
    }
    else
    {
        newRotation = nowRotation;
    }

    switch (mSelectedLayer->layerType)
    {
    case eLayerType::SHAPE:
        static_cast<ShapeLayer *>(mSelectedLayer)->SetRotation(newRotation);
        break;

    default:
        break;
    }
}

void InspectorCanvas::setRotationZ(std::string str)
{
    if (!mSelectedLayer)
        return;

    glm::vec3 nowRotation = mSelectedLayer->GetRotation();
    glm::vec3 newRotation;
    if (!str.empty())
    {
        newRotation = glm::vec3(nowRotation.x, nowRotation.y, std::stof(str));
    }
    else
    {
        newRotation = nowRotation;
    }

    switch (mSelectedLayer->layerType)
    {
    case eLayerType::SHAPE:
        static_cast<ShapeLayer *>(mSelectedLayer)->SetRotation(newRotation);
        break;

    default:
        break;
    }
}

void InspectorCanvas::SetColor(glm::vec3 color)
{
    if(mSelectedLayer->layerType!=eLayerType::SHAPE)
        return;
    
    static_cast<
}

void InspectorCanvas::SetInspector(Layer *layer)
{
    mSelectedLayer = layer;
    mPositionTextBoxX->SetText(std::to_string(layer->GetPosition().x));
    mPositionTextBoxY->SetText(std::to_string(layer->GetPosition().y));
    mPositionTextBoxZ->SetText(std::to_string(layer->GetPosition().z));

    mRotationTextBoxX->SetText(std::to_string(layer->GetRotation().x));
    mRotationTextBoxY->SetText(std::to_string(layer->GetRotation().y));
    mRotationTextBoxZ->SetText(std::to_string(layer->GetRotation().z));

    // mScaleTextBoxX->SetText(std::to_string(layer->GetScale().x));
    // mScaleTextBoxY->SetText(std::to_string(layer->GetScale().y));
    // mScaleTextBoxZ->SetText(std::to_string(layer->GetScale().z));
}

void InspectorCanvas::Rendering()
{
    for (auto const &child : mChild)
    {
        if (child->GetVisible())
        {
            child->Draw();
        }
    }
}