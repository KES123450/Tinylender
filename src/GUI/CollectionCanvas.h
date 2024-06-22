
#include <glm/glm.hpp>
#include "LayerUI.h"
#include "../Layer.h"
#include "../IPressed.h"
#include "../IPressedUp.h"
#include "../IPressedDown.h"
#pragma once
class Collection;


class CollectionCanvas : public IPressed, public IPressedDown, public IPressedUp{
    public:
        CollectionCanvas();
        void AddLayerUI(Layer* layer);
        void Rendering(LayerUI* layer, int depth=0,int count=0);
        void OnPointer(float xpos, float ypos,float xdelta,float ydelta) override;
        void OnPointerUp(float xpos, float ypos,float xdelta,float ydelta) override;
        void OnPointerDown(float xpos, float ypos,float xdelta,float ydelta) override;
        LayerUI* GetRootLayerUI() {return mRootLayerUI;}

    private:
        float mLayerOffsetY=0.2f; //전부 NDC
        float mLayerSizeX=0.4f;
        float mLayerSizeY=0.15f;
        float mDepthOfssetX=0.2f;
        int mCount=0;
        LayerUI* mRootLayerUI;
        LayerUI* mPrevSelectedLayerUI=nullptr;

        int countNodes(LayerUI* layer);
        int findLayer(float yPos,LayerUI* layer);
        LayerUI* findLayer(LayerUI* layerUI);
};