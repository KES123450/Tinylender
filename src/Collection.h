

#include "Mesh.h"
#include <vector>
#include <tuple>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shader/Shader.h"
#include "Layer.h"
#include "ShapeLayer.h"
#include "LightLayer.h"
#include "GUI/CollectionCanvas.h"

#pragma once

class Collection
{
public:
    Collection();
    static Collection *GetInstance();
    Layer *GetSelectedLayer() const { return mSelectedLayer; }
    Layer *GetRootLayer() const { return mRootLayer; }
    // std::vector<Mesh*> GetModel() const{return mMeshes;}

    void AddLayer(Layer *layer, eLayerType layerType);
    void AddLayer(Layer *layer);
    void SelectLayer(Layer *selected);
    void Rendering(Layer *layer);
    void SetCollectionCanvas(CollectionCanvas *col);

private:
    static Collection *instance;
    CollectionCanvas *mCollectionCanvas = nullptr;
    Layer *mRootLayer = new Layer();
    Layer *mSelectedLayer = mRootLayer;
    unsigned int lightsUBO;
    unsigned int mLightCount = 0;
};
