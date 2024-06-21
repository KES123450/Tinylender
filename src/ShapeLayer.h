
#include "Layer.h"
#include "Mesh.h"
#include "constants.h"

#pragma once

class ShapeLayer : public Layer{
    public:
        ShapeLayer() {};
        ShapeLayer(Mesh* m);
        Mesh* mesh;

};
