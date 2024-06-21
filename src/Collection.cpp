#include "Collection.h"

Collection* Collection::instance = nullptr;

Collection* Collection::GetInstance(){
    if(instance==NULL)
        instance = new Collection();
    return instance;
}


void Collection::SetCollectionCanvas(CollectionCanvas* col){
    mCollectionCanvas = col;
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
    mCollectionCanvas->AddLayerUI(newLayer);
}

void Collection::AddLayer(Layer* layer){
    mRootLayer->children.push_back(layer);
    mCollectionCanvas->AddLayerUI(layer);
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