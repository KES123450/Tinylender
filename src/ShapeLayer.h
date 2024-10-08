#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Layer.h"
#include "Mesh.h"
#include "constants.h"
#include "Shader/Shader.h"

#pragma once

class ShapeLayer : public Layer
{
    public:
        ShapeLayer():mShader("Shader/vertexShader.glsl", "Shader/fragmentShader.glsl") {};
        ShapeLayer(Mesh* m, std::string name);
        void SetPosition(glm::vec3 pos);
        void SetRotation(glm::vec3 rot);
        void SetScale(glm::vec3 scale);
        void SetColor(glm::vec3 color);
        void Draw();
        Mesh* mesh;
    
    private:
        glm::vec3 mColor;
        unsigned int mUniformBlockIndex;
        Shader mShader;
        

};
