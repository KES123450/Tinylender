
#include <glm/glm.hpp>
#include <cmath>
#include "LayerUI.h"
#include "../Layer.h"
#include "../IPressed.h"
#include "../IPressedUp.h"
#include "../IPressedDown.h"
#include "../IScrolled.h"
#pragma once
class Collection;

class CollectionCanvas : public IPressed, public IPressedDown, public IPressedUp, public IScrolled
{
public:
    CollectionCanvas();
    void AddLayerUI(Layer *layer);
    void Rendering();
    void RenderingLayer(LayerUI *layer, int depth = 0, int count = 0);
    void OnPointer(float xpos, float ypos, float xdelta, float ydelta) override;
    void OnPointerUp(float xpos, float ypos, float xdelta, float ydelta) override;
    void OnPointerDown(float xpos, float ypos, float xdelta, float ydelta) override;
    void OnScroll(float xoffset, float yoffset) override;
    void ScrollLayer(LayerUI *layer, float xoffset, float yoffset, int depth = 0, int count = 0);
    LayerUI *GetRootLayerUI() { return mRootLayerUI; }

private:
    float mLayerOffsetY = 0.12439024390243902f; // 전부 NDC
    float mLayerSizeX = 0.3111111111111111f;
    float mLayerSizeY = 0.08351219512195122f;
    float mDepthOfssetX = 0.2f;
    float mScrollDiscanceY = 0; // NDC
    int mCount = 0;
    LayerUI *mRootLayerUI;
    LayerUI *mPrevSelectedLayerUI = nullptr;

    Shader *mMaskShader;
    unsigned int mMaskVBO;
    unsigned int mMaskVAO;
    unsigned int mMaskEBO;
    unsigned int mMaskIndices[6] = {
        0, 1, 2,
        2, 1, 3};

    int countNodes(LayerUI *layer);
    int findLayer(float yPos, LayerUI *layer);
    LayerUI *findLayer(LayerUI *layerUI);
    void drawMask();
};