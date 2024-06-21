
#include "IState.h"
#include "IPressedDown.h"
#include "IPressed.h"
#include "IPressedUp.h"
#include "Collection.h"
#include "Mesh.h"
#include "Vertex.h"
#include "Layer.h"
#include "ShapeLayer.h"
#include <vector>
#include <glm/glm.hpp>
#include <iostream>

#pragma once

class Extrude:public IState, public IPressedDown ,public IPressed, public IPressedUp{
    public:
        void Handle() override;
        void HandleOut() override;
        void OnPointerDown(float xpos, float ypos,float xdelta,float ydelta) override;
        void OnPointer(float xpos, float ypos,float xdelta,float ydelta) override;
        void OnPointerUp(float xpos, float ypos,float xdelta,float ydelta) override;

    private:
        bool bState=false;
        bool bShape=false; // 임시땜빵
        std::vector<Vertex> mCurrentVertices;
        std::vector<Vertex> mNewVertices;
        std::vector<Vertex> mVertices;
        std::vector<std::vector<unsigned int>> mFaces;
        std::vector<glm::vec3> mFacesNormal;

        void selectFace();
        void extrudeMesh(float xdelta, float ydelta);
        void setVertexNormal();
};
