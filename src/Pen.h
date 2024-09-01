

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <algorithm>
#include "Vertex.h"
#include "Mesh.h"
#include "IPressedDown.h"
#include "IPressed.h"
#include "IPressedUp.h"
#include "IMoved.h"
#include "IState.h"
#include "Collection.h"
#include "ShapeLayer.h"
#include "constants.h"
#include "Utils.h"

#pragma once
extern glm::mat4 view;
extern glm::mat4 projection;
extern glm::vec3 cameraFront;

class Pen : public IPressedDown, public IPressed, public IPressedUp, public IMoved, public IState
{
public:
    Pen();
    void DrawMesh();
    void OnPointerDown(float xpos, float ypos, float xdelta, float ydelta) override;
    void OnPointer(float xpos, float ypos, float xdelta, float ydelta) override;
    void OnPointerUp(float xpos, float ypos, float xdelta, float ydelta) override;
    void OnMove(float xpos, float ypos, float xdelta, float ydelta) override;
    void Handle() override;
    void HandleOut() override;

private:
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndice;
    unsigned int mVBO;
    unsigned int mVAO;
    unsigned int mEBO;

    float mLineVertices[9] = {0};
    unsigned int mLineVBO;
    unsigned int mLineVAO;

    float mSplineVertices[270] = {0};
    unsigned int mSplineVBO;
    unsigned int mSplineVAO;

    bool bDraw = false;
    bool bPressed = false;
    bool bCurve = false;
    bool bCurve2nd = false;
    bool bCurve3rd = false;
    bool bFirst = true;
    glm::vec3 mNowPoint;
    glm::vec3 mControlPoint1;

    std::vector<glm::vec3> bezierSpline(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, int pointNum);
    std::vector<glm::vec3> bezierSpline(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4, int pointNum);
};
