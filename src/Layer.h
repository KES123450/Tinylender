
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "constants.h"

#pragma once

class Layer{
    public:
        std::string name;
        std::vector<Layer*> children;
        eLayerType layerType=eLayerType::EMPTY;
    
        void SetPosition(glm::vec3 pos);
        void SetRotation(glm::vec3 rot);
        void SetScale(glm::vec3 scale);
        glm::vec3 GetPosition() const {return mPosition;}
        glm::vec3 GetRotation() const {return mRotation;}
        glm::vec3 GetScale() const {return mScale;}
        void SetVisible(bool v);
        bool GetVisible() const {return mVisible;}

    private:
        glm::vec3 mPosition = glm::vec3(0.0f);
        glm::vec3 mRotation = glm::vec3(0.00001f);
        glm::vec3 mScale = glm::vec3(1.0f);
        bool mVisible = true;
};