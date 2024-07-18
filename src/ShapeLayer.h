
#include "Layer.h"
#include "Mesh.h"
#include "constants.h"
#include "Shader/Shader.h"

#pragma once

class ShapeLayer : public Layer{
    public:
        ShapeLayer() {};
        ShapeLayer(Mesh* m, std::string name);
        void Draw();
        Mesh* mesh;
    
    private:
        Shader* shader;

};
