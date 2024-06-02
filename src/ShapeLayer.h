#include "Layer.h"
#include "Mesh.h"

#pragma once

class ShapeLayer : public Layer{
    public:
        ShapeLayer() {};
        ShapeLayer(Mesh* m);
        Mesh* mesh;

};

ShapeLayer::ShapeLayer(Mesh* m){
    layerType=eLayerType::SHAPE;
    mesh=m;
}