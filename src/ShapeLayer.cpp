#include "ShapeLayer.h"

ShapeLayer::ShapeLayer(Mesh* m, std::string name){
    this->name = name;
    layerType=eLayerType::SHAPE;
    mesh=m;
    
}

