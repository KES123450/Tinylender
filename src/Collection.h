

#include "Mesh.h"
#include <vector>
#include "Shader/Shader.h"
#include "Layer.h"
#include "ShapeLayer.h"
#include "GUI/CollectionCanvas.h"

#pragma once

class Collection{
    public:
        static Collection* GetInstance();
        Layer* GetSelectedLayer() const {return mSelectedLayer;}
        Layer* GetRootLayer() const {return mRootLayer;}
        //std::vector<Mesh*> GetModel() const{return mMeshes;}

        void AddLayer(Layer* layer,eLayerType layerType);
        void AddLayer(Layer* layer);
        void SelectLayer(Layer* selected);
        void Rendering(Layer* layer);
        void SetCollectionCanvas(CollectionCanvas* col);

    private:
        static Collection* instance;
        CollectionCanvas* mCollectionCanvas=nullptr;
        Layer* mRootLayer = new Layer();
        Layer* mSelectedLayer=mRootLayer;

};
