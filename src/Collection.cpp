#include "Collection.h"

Collection *Collection::instance = nullptr;

Collection::Collection()
{
    glGenBuffers(1, &lightsUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(float) * 4 * 2 * 32, NULL, GL_STATIC_DRAW);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, lightsUBO, 0, sizeof(float) * 4 * 2 * 32);
}

Collection *Collection::GetInstance()
{
    if (instance == NULL)
        instance = new Collection();
    return instance;
}

void Collection::SetCollectionCanvas(CollectionCanvas *col)
{
    mCollectionCanvas = col;
}

void Collection::SelectLayer(Layer *selected)
{
    mSelectedLayer = selected;
}

// 얜 왜만든거지??
void Collection::AddLayer(Layer *layer, eLayerType layerType)
{
    Layer *newLayer;
    switch (layerType)
    {
    case eLayerType::SHAPE:
        newLayer = new ShapeLayer();
        break;

    case eLayerType::LIGHT:
        newLayer = new LightLayer();

        break;

    default:
        break;
    }

    mRootLayer->children.push_back(newLayer);
    mCollectionCanvas->AddLayerUI(newLayer);
}

void Collection::AddLayer(Layer *layer)
{
    eLayerType type = layer->layerType;
    switch (type)
    {
    case eLayerType::EMPTY:
        break;

    case eLayerType::SHAPE:
        mRootLayer->children.push_back(layer);
        mCollectionCanvas->AddLayerUI(layer);
        break;

    case eLayerType::LIGHT:
        mRootLayer->children.push_back(layer);
        mCollectionCanvas->AddLayerUI(layer);
        mLightCount++;
        static_cast<LightLayer *>(layer)->SetIndex(mLightCount);
        break;

    default:
        break;
    }
}

void Collection::Rendering(Layer *layer)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (layer->GetVisible() && layer->layerType == eLayerType::SHAPE)
    {
        static_cast<ShapeLayer *>(layer)->Draw();
    }

    if (layer->GetVisible() && layer->layerType == eLayerType::LIGHT)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
        static_cast<LightLayer *>(layer)->Draw();
    }

    if (layer->children.size() == 0)
        return;

    for (Layer *child : mRootLayer->children)
    {
        Rendering(child);
    }
}