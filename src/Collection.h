#include "Mesh.h"
#include <vector>
#include "Shader/Shader.h"
#include "Layer.h"
#include "ShapeLayer.h"

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

    private:
        static Collection* instance;
        Layer* mRootLayer = new Layer();
        Layer* mSelectedLayer=mRootLayer;

};

Collection* Collection::instance = nullptr;

Collection* Collection::GetInstance(){
    if(instance==NULL)
        instance = new Collection();
    return instance;
}

void Collection::SelectLayer(Layer* selected){
    mSelectedLayer = selected;
}

void Collection::AddLayer(Layer* layer,eLayerType layerType){
    Layer* newLayer;
    switch (layerType)
    {
        case eLayerType::SHAPE:
            newLayer= new ShapeLayer();
            break;

        default:
            break;
    }

    mRootLayer->children.push_back(newLayer);
}

void Collection::AddLayer(Layer* layer){
    mRootLayer->children.push_back(layer);
}

void Collection::Rendering(Layer* layer){
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    if(layer->visible&&layer->layerType==eLayerType::SHAPE){
        static_cast<ShapeLayer*>(layer)->mesh->Draw();
    }
    
    if(layer->children.size()==0)
        return;

    for(Layer* child : mRootLayer->children){
        Rendering(child);
    }
}