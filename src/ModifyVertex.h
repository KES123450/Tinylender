

#include <glm/glm.hpp>
#include <vector>
#include "Collection.h"
#include "IPressed.h"
#include "IPressedDown.h"
#include "IPressedUp.h"
#include "IState.h"
#include "Mesh.h"
#include "Vertex.h"
#include "constants.h"
#include "Layer.h"

#pragma once

extern glm::mat4 view;
extern glm::mat4 projection;
extern glm::vec3 cameraFront;

class ModifyVertex : public IPressedDown, public IPressed, public IPressedUp, public IState
{
public:
    void OnPointer(float xpos, float ypos, float xdelta, float ydelta) override;
    void OnPointerDown(float xpos, float ypos, float xdelta, float ydelta) override;
    void OnPointerUp(float xpos, float ypos, float xdelta, float ydelta) override;
    void Handle() override;
    void HandleOut() override {};

private:
    bool bPushed = false;
    bool bFindVertex = false;
    float mDeltaX, mDeltaY;
    int mSelectedIdx = 0;
    glm::vec2 coordinatelocalToScreen(float x, float y, float z);
    bool searchVertex(float xpos, float ypos);
};
