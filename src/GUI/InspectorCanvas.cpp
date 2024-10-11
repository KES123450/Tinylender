#include "InspectorCanvas.h"

InspectorCanvas::InspectorCanvas(Layer *rootLayer)
{
    mSelectedLayer = rootLayer;

    std::array<std::tuple<glm::vec3, glm::vec3, const char *>, 21> buttonDatas = {
        std::make_tuple(glm::vec3(0.72588f, 0.4585f, 0.0f), glm::vec3(0.9764f, 0.2549f, 0.4862f), "resource/Color/Color1.png"),
        std::make_tuple(glm::vec3(0.76447f, 0.4585f, 0.0f), glm::vec3(0.9568f, 0.2313f, 0.2549f), "resource/Color/Color2.png"),
        std::make_tuple(glm::vec3(0.803068f, 0.4585f, 0.0f), glm::vec3(228.0f / 255.0f, 69.0f / 255.0f, 242.0f / 255.0f), "resource/Color/Color3.png"),
        std::make_tuple(glm::vec3(0.8416f, 0.4585f, 0.0f), glm::vec3(134.0f / 255.0f, 67.0f / 255.0f, 242.0f / 255.0f), "resource/Color/Color4.png"),
        std::make_tuple(glm::vec3(0.88023f, 0.4585f, 0.0f), glm::vec3(59.0f / 255.0f, 52.0f / 255.0f, 237.0f / 255.0f), "resource/Color/Color5.png"),
        std::make_tuple(glm::vec3(0.91882f, 0.4585f, 0.0f), glm::vec3(51.0f / 255.0f, 138.0f / 255.0f, 251.0f / 255.0f), "resource/Color/Color6.png"),
        std::make_tuple(glm::vec3(0.95741f, 0.4585f, 0.0f), glm::vec3(86.0f / 255.0f, 198.0f / 255.0f, 235.0f / 255.0f), "resource/Color/Color7.png"),

        std::make_tuple(glm::vec3(0.7258f, 0.3853f, 0.0f), glm::vec3(139.0f / 255.0f, 214.0f / 255.0f, 237.0f / 255.0f), "resource/Color/Color8.png"),
        std::make_tuple(glm::vec3(0.7644f, 0.3853f, 0.0f), glm::vec3(96.0f / 255.0f, 236.0f / 255.0f, 178.0f / 255.0f), "resource/Color/Color9.png"),
        std::make_tuple(glm::vec3(0.80306f, 0.3853f, 0.0f), glm::vec3(166.0f / 255.0f, 243.0f / 255.0f, 95.0f / 255.0f), "resource/Color/Color10.png"),
        std::make_tuple(glm::vec3(0.8416f, 0.3853f, 0.0f), glm::vec3(204.0f / 255.0f, 243.0f / 255.0f, 86.0f / 255.0f), "resource/Color/Color11.png"),
        std::make_tuple(glm::vec3(0.8802f, 0.3853f, 0.0f), glm::vec3(244.0f / 255.0f, 215.0f / 255.0f, 69.0f / 255.0f), "resource/Color/Color12.png"),
        std::make_tuple(glm::vec3(0.9188f, 0.3853f, 0.0f), glm::vec3(240.0f / 255.0f, 127.0f / 255.0f, 62.0f / 255.0f), "resource/Color/Color13.png"),
        std::make_tuple(glm::vec3(0.9574f, 0.3853f, 0.0f), glm::vec3(250.0f / 255.0f, 122.0f / 255.0f, 156.0f / 255.0f), "resource/Color/Color14.png"),

        std::make_tuple(glm::vec3(0.7258f, 0.3119f, 0.0f), glm::vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f), "resource/Color/Color15.png"),
        std::make_tuple(glm::vec3(0.7644f, 0.3119f, 0.0f), glm::vec3(32.0f / 255.0f, 32.0f / 255.0f, 32.0f / 255.0f), "resource/Color/Color16.png"),
        std::make_tuple(glm::vec3(0.80306f, 0.3119f, 0.0f), glm::vec3(77.0f / 255.0f, 77.0f / 255.0f, 77.0f / 255.0f), "resource/Color/Color17.png"),
        std::make_tuple(glm::vec3(0.8416f, 0.3119f, 0.0f), glm::vec3(126.0f / 255.0f, 126.0f / 255.0f, 126.0f / 255.0f), "resource/Color/Color18.png"),
        std::make_tuple(glm::vec3(0.8802f, 0.3119f, 0.0f), glm::vec3(182.0f / 255.0f, 182.0f / 255.0f, 182.0f / 255.0f), "resource/Color/Color19.png"),
        std::make_tuple(glm::vec3(0.9188f, 0.3119f, 0.0f), glm::vec3(238.0f / 255.0f, 238.0f / 255.0f, 238.0f / 255.0f), "resource/Color/Color20.png"),
        std::make_tuple(glm::vec3(0.9574f, 0.3119f, 0.0f), glm::vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f), "resource/Color/Color21.png"),
    };

    for (int i = 0; i < 21; i++)
    {
        mButtons[i] = new Button(std::get<0>(buttonDatas[i]), 0.02395f, 0.04390f, std::get<2>(buttonDatas[i]), eImageType::PNG);
        glm::vec3 color = std::get<1>(buttonDatas[i]);
        auto BtnCallback = [this, color](double xpos, double ypos)
        {
            this->SetColor(color);
        };
        mButtons[i]->SetbuttonCallback(std::function<void(double, double)>(BtnCallback));
        AddWidget(mButtons[i]);
    }

    mInspectorPanel = new Panel(glm::vec3(0.8443113772455091f, -0.06008536585365842f, 0.0f), 0.31137724550898205f, 1.879829268292683, "resource/inspector.png", eImageType::PNG);
    AddWidget(mInspectorPanel);

    mPositionTextBoxX = new TextBox(glm::vec3(0.8196939454424483f, 0.7682926829268293f, 0.0f), 0.0385894876912841f, 0.02926829268292683f, "1", 0.3f, glm::vec3(0.85098039215f, 0.85098039215f, 0.85098039215f), false, 1.0f);
    InputEventSystem::GetInstance()->AddPressedDown(mPositionTextBoxX);
    InputEventSystem::GetInstance()->AddPressed(mPositionTextBoxX);
    InputEventSystem::GetInstance()->AddPressedUp(mPositionTextBoxX);
    InputEventSystem::GetInstance()->AddKeyDown(mPositionTextBoxX);
    mPositionTextBoxX->SetEventCallback([this](std::string str)
                                        { setPositionX(str); });
    AddWidget(mPositionTextBoxX);

    mPositionTextBoxY = new TextBox(glm::vec3(0.8875582168995342f, 0.7682926829268293f, 0.0f), 0.0385894876912841f, 0.02926829268292683f, "1", 0.3f, glm::vec3(0.85098039215f, 0.85098039215f, 0.85098039215f), false, 1.0f);
    InputEventSystem::GetInstance()->AddPressedDown(mPositionTextBoxY);
    InputEventSystem::GetInstance()->AddPressed(mPositionTextBoxY);
    InputEventSystem::GetInstance()->AddPressedUp(mPositionTextBoxY);
    InputEventSystem::GetInstance()->AddKeyDown(mPositionTextBoxY);
    mPositionTextBoxY->SetEventCallback([this](std::string str)
                                        { setPositionY(str); });
    AddWidget(mPositionTextBoxY);

    mPositionTextBoxZ = new TextBox(glm::vec3(0.95542248835662f, 0.7682926829268293f, 0.0f), 0.0385894876912841f, 0.02926829268292683f, "1", 0.3f, glm::vec3(0.85098039215f, 0.85098039215f, 0.85098039215f), false, 1.0f);
    InputEventSystem::GetInstance()->AddPressedDown(mPositionTextBoxZ);
    InputEventSystem::GetInstance()->AddPressed(mPositionTextBoxZ);
    InputEventSystem::GetInstance()->AddPressedUp(mPositionTextBoxZ);
    InputEventSystem::GetInstance()->AddKeyDown(mPositionTextBoxZ);
    mPositionTextBoxY->SetEventCallback([this](std::string str)
                                        { setPositionZ(str); });
    AddWidget(mPositionTextBoxZ);

    mRotationTextBoxX = new TextBox(glm::vec3(0.8196939454424483f, 0.7012195121951219f, 0.0f), 0.0385894876912841f, 0.02926829268292683f, "1", 0.3f, glm::vec3(0.85098039215f, 0.85098039215f, 0.85098039215f), false, 1.0f);
    InputEventSystem::GetInstance()->AddPressedDown(mRotationTextBoxX);
    InputEventSystem::GetInstance()->AddPressed(mRotationTextBoxX);
    InputEventSystem::GetInstance()->AddPressedUp(mRotationTextBoxX);
    InputEventSystem::GetInstance()->AddKeyDown(mRotationTextBoxX);
    mRotationTextBoxX->SetEventCallback([this](std::string str)
                                        { setRotationX(str); });
    AddWidget(mRotationTextBoxX);

    mRotationTextBoxY = new TextBox(glm::vec3(0.8875582168995342f, 0.7012195121951219f, 0.0f), 0.0385894876912841f, 0.02926829268292683f, "1", 0.3f, glm::vec3(0.85098039215f, 0.85098039215f, 0.85098039215f), false, 1.0f);
    InputEventSystem::GetInstance()->AddPressedDown(mRotationTextBoxY);
    InputEventSystem::GetInstance()->AddPressed(mRotationTextBoxY);
    InputEventSystem::GetInstance()->AddPressedUp(mRotationTextBoxY);
    InputEventSystem::GetInstance()->AddKeyDown(mRotationTextBoxY);
    mRotationTextBoxY->SetEventCallback([this](std::string str)
                                        { setRotationY(str); });
    AddWidget(mRotationTextBoxY);

    mRotationTextBoxZ = new TextBox(glm::vec3(0.95542248835662f, 0.7012195121951219f, 0.0f), 0.0385894876912841f, 0.02926829268292683f, "1", 0.3f, glm::vec3(0.85098039215f, 0.85098039215f, 0.85098039215f), false, 1.0f);
    InputEventSystem::GetInstance()->AddPressedDown(mRotationTextBoxZ);
    InputEventSystem::GetInstance()->AddPressed(mRotationTextBoxZ);
    InputEventSystem::GetInstance()->AddPressedUp(mRotationTextBoxZ);
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

    case eLayerType::LIGHT:
        static_cast<LightLayer *>(mSelectedLayer)->SetPosition(newPosition);
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

    case eLayerType::LIGHT:
        static_cast<LightLayer *>(mSelectedLayer)->SetPosition(newPosition);
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
    
    case eLayerType::LIGHT:
        static_cast<LightLayer *>(mSelectedLayer)->SetPosition(newPosition);
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
    if (mSelectedLayer->layerType == eLayerType::SHAPE)
    {
        static_cast<ShapeLayer *>(mSelectedLayer)->SetColor(color);
        return;
    }

    if (mSelectedLayer->layerType == eLayerType::LIGHT)
    {
        static_cast<LightLayer *>(mSelectedLayer)->SetColor(color);
        return;
    }
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

void InspectorCanvas::OnPointerUp(float xpos, float ypos, float xdelta, float ydelta)
{
    float ndcX = (2 * xpos / SCR_WIDTH) - 1;
    float ndcY = 1 - (2 * ypos / SCR_HEIGHT);

    for (Widget *child : mChild)
    {
        if (child->GetType() != eUIType::BUTTON)
            continue;
        Button *b = static_cast<Button *>(child);
        glm::vec3 pos = b->GetPos();
        glm::vec2 size = b->GetSize();
        glm::vec2 sizeHalf = glm::vec2(size.x / 2, size.y / 2);

        if (ndcX >= (pos.x - sizeHalf.x) && ndcX <= (pos.x + sizeHalf.x) && ndcY >= (pos.y - sizeHalf.y) && ndcY <= (pos.y + sizeHalf.y))
        {
            if (b->getButtonCallback() != NULL)
                b->Callbtn();
        }
    }
}
