#include "ModifyVertex.h"

void ModifyVertex::Handle()
{
    Layer *layer = Collection::GetInstance()->GetSelectedLayer();
    if (layer->layerType != eLayerType::SHAPE)
    {
        return;
    }

    if (bPushed && bFindVertex)
    {
        Mesh *selectMesh = static_cast<ShapeLayer *>(layer)->mesh;
        unsigned int VBO = static_cast<ShapeLayer *>(layer)->mesh->GetVBO();
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 right = glm::normalize(glm::cross(up, -(cameraFront)));

        Vertex offset = selectMesh->vertices[mSelectedIdx];
        offset.Position.x += mDeltaX * right.x * MODIFY_VERTEX_SPEED;
        offset.Position.y += -mDeltaY * MODIFY_VERTEX_SPEED;
        offset.Position.z += mDeltaX * right.z * MODIFY_VERTEX_SPEED;

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, mSelectedIdx * sizeof(Vertex), sizeof(offset), &offset);

        selectMesh->vertices[mSelectedIdx].Position.x += mDeltaX * right.x * MODIFY_VERTEX_SPEED;
        selectMesh->vertices[mSelectedIdx].Position.y += -mDeltaY * MODIFY_VERTEX_SPEED;
        selectMesh->vertices[mSelectedIdx].Position.z += mDeltaX * right.z * MODIFY_VERTEX_SPEED;
    }
}

void ModifyVertex::OnPointerDown(float xpos, float ypos, float xdelta, float ydelta)
{
    bPushed = true;
    if (searchVertex(xpos, ypos))
    {
        bFindVertex = true;
    }
}

void ModifyVertex::OnPointer(float xpos, float ypos, float xdelta, float ydelta)
{
    mDeltaX = xdelta;
    mDeltaY = ydelta;
}

void ModifyVertex::OnPointerUp(float xpos, float ypos, float xdelta, float ydelta)
{
    bPushed = false;
    bFindVertex = false;
}

glm::vec2 ModifyVertex::coordinatelocalToScreen(float x, float y, float z)
{ //[TODO] 나중에 static으로 유틸함수로 빼버리기
    glm::vec4 local = glm::vec4(x, y, z, 1.0f);
    glm::vec4 viewCoord = view * local;
    glm::vec4 clipCoord = projection * viewCoord;
    glm::vec3 ndc = glm::vec3(clipCoord) / clipCoord.w;
    glm::vec2 screen = glm::vec2((ndc.x + 1) * (SCR_WIDTH / 2), (ndc.y + 1) * (SCR_HEIGHT / 2));

    return screen;
}

bool ModifyVertex::searchVertex(float xpos, float ypos)
{
    Layer *layer = Collection::GetInstance()->GetSelectedLayer();
    if (layer->layerType != eLayerType::SHAPE)
    {
        return false;
    }
    Mesh *model = static_cast<ShapeLayer *>(layer)->mesh;

    for (int i = 0; i < model->vertices.size(); i++)
    {
        glm::vec2 screenMesh = coordinatelocalToScreen(model->vertices[i].Position.x, model->vertices[i].Position.y, model->vertices[i].Position.z);
        if (abs(screenMesh.x - xpos) <= 70 && abs(screenMesh.y - (SCR_HEIGHT - ypos)) <= 70)
        {
            mSelectedIdx = i;
            return true;
        }
    }

    return false;
}