#include "ShapeLayer.h"

ShapeLayer::ShapeLayer(Mesh *m, std::string name)
    : mShader("Shader/vertexShader.glsl", "Shader/fragmentShader.glsl")
{
    this->name = name;
    layerType = eLayerType::SHAPE;
    mesh = m;
}

void ShapeLayer::Draw()
{

    mShader.use();

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, GetPosition());
    transform = glm::rotate(transform, glm::length(GetRotation()), GetRotation());
    unsigned int modelLoc = glGetUniformLocation(mShader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));

    for (unsigned int i = 0; i < mesh->GetTexture().size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, mesh->GetTexture()[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(mesh->GetVAO());
    glDrawArrays(GL_TRIANGLES, 0, mesh->GetVerticeCount());
}

void ShapeLayer::SetPosition(glm::vec3 pos)
{
    Layer::SetPosition(pos);
    mShader.use();
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, pos);

    unsigned int modelLoc = glGetUniformLocation(mShader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

void ShapeLayer::SetRotation(glm::vec3 rot)
{
    Layer::SetRotation(rot);
}

void ShapeLayer::SetScale(glm::vec3 scale)
{
}

void ShapeLayer::SetColor(glm::vec3 color)
{
}