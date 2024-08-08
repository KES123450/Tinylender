#include "Pen.h"

Pen::Pen()
{
    mVertices.push_back({glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f), glm::vec3(0.0f)});
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_DYNAMIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndice.size() * sizeof(unsigned int), &mIndice[0], GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Color));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);

    glGenVertexArrays(1, &mLineVAO);
    glGenBuffers(1, &mLineVBO);

    glBindVertexArray(mLineVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mLineVBO);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), &mLineVertices[0], GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    glBindVertexArray(0);

    glGenVertexArrays(1, &mSplineVAO);
    glGenBuffers(1, &mSplineVBO);

    glBindVertexArray(mSplineVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mSplineVBO);
    glBufferData(GL_ARRAY_BUFFER, 270 * sizeof(float), &mSplineVertices[0], GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    glBindVertexArray(0);
}

void Pen::Handle()
{
    bDraw = true;
    DrawMesh();
}

void Pen::HandleOut()
{
    bDraw = false;
}

void Pen::DrawMesh()
{

    if (mVertices.size() < 2)
        return;

    if (mVertices.size() == 2)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBindVertexArray(mVAO);

        glDrawArrays(GL_LINES, 0, 2);
        glBindVertexArray(0);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindVertexArray(mVAO);
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
        glBindVertexArray(0);
    }

    if (bPressed || bCurve2nd)
    {
        glBindVertexArray(mSplineVAO);
        glBindBuffer(GL_ARRAY_BUFFER, mSplineVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 270 * sizeof(float), &mSplineVertices[0]);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, 270);
    }
    else
    {
        glBindVertexArray(mLineVAO);
        glBindBuffer(GL_ARRAY_BUFFER, mLineVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(float), 3 * sizeof(float), &mLineVertices[3]);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, 9);
    }
}

void Pen::OnPointerDown(float xpos, float ypos, float xdelta, float ydelta)
{
    printf("%s", "  down  ");
    if (!bDraw)
        return;

    mNowPoint = ScreenToNDC(glm::vec2(xpos, ypos));
}

void Pen::OnPointer(float xpos, float ypos, float xdelta, float ydelta)
{
    printf("%s", "  press  ");
    if (!bDraw)
        return;

    bPressed = true;
}

void Pen::OnPointerUp(float xpos, float ypos, float xdelta, float ydelta)
{
    if (!bDraw)
        return;

    if (glm::length(mNowPoint - mVertices[0].Position) <= 0.1f && mVertices.size() > 3)
    {
        printf("%s", "  done  \n");
        // mesh로 만들어서 collection에 추가
        std::vector<std::vector<unsigned int>> faces;
        std::vector<unsigned int> f;
        faces.push_back(f);

        for (int i = 0; i < mVertices.size(); i++)
        {
            faces[0].push_back(i);
            faces[0].push_back(i);
            faces[0].push_back(i);
        }

        Mesh *mesh = new Mesh(mVertices, mIndice, std::vector<Texture>(0), faces, "Shader/vertexShader.glsl", "Shader/fragmentShader.glsl");
        ShapeLayer *shape = new ShapeLayer(mesh, std::to_string(mVertices.size()));
        Collection::GetInstance()->AddLayer(shape);

        mVertices.clear();
        mVertices.push_back({glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.0f), glm::vec3(0.0f)});
        mIndice.clear();
        bFirst = true;
    }
    else
    {
        Vertex vert = {mNowPoint, glm::vec3(1.0f), glm::vec2(1.0f), glm::vec3(1.0f)};

        mLineVertices[0] = mNowPoint.x;
        mLineVertices[1] = mNowPoint.y;
        mLineVertices[2] = mNowPoint.z;

        if (bFirst)
        {
            mVertices[0] = vert;
            mLineVertices[6] = vert.Position.x;
            mLineVertices[7] = vert.Position.y;
            mLineVertices[8] = vert.Position.z;

            glBindBuffer(GL_ARRAY_BUFFER, mLineVBO);
            glBufferSubData(GL_ARRAY_BUFFER, 6 * sizeof(float), 3 * sizeof(float), &mLineVertices[6]);
        }
        else
        {
            if (bCurve)
            {
                glm::vec3 controlPoint = ScreenToNDC(glm::vec2(xpos, ypos));
                Vertex temp = mVertices[mVertices.size() - 1];
                std::vector<glm::vec3> bezierPoints = bezierSpline(mVertices[mVertices.size() - 1].Position, controlPoint, mNowPoint, 30);
                for (int i = 0; i < 29; i++)
                {
                    mVertices.push_back(mVertices[0]);
                    mVertices.push_back(Vertex{bezierPoints[i], glm::vec3(1.0f), glm::vec2(1.0f), glm::vec3(1.0f)});
                    mVertices.push_back(Vertex{bezierPoints[i + 1], glm::vec3(1.0f), glm::vec2(1.0f), glm::vec3(1.0f)});
                }
                mVertices.push_back(mVertices[0]);
                mVertices.push_back(Vertex{bezierPoints[29], glm::vec3(1.0f), glm::vec2(1.0f), glm::vec3(1.0f)});
                mVertices.push_back(vert);

                bCurve2nd = true;
                mControlPoint1 = mNowPoint + mNowPoint - controlPoint;
            }
            else if (bCurve2nd)
            {
                glm::vec3 controlPoint = ScreenToNDC(glm::vec2(xpos, ypos));
                std::vector<glm::vec3> bezierPoints = bezierSpline(mVertices[mVertices.size() - 1].Position, mControlPoint1, controlPoint, 30);
                for (int i = 0; i < 29; i++)
                {
                    mVertices.push_back(mVertices[0]);
                    mVertices.push_back(Vertex{bezierPoints[i], glm::vec3(1.0f), glm::vec2(1.0f), glm::vec3(1.0f)});
                    mVertices.push_back(Vertex{bezierPoints[i + 1], glm::vec3(1.0f), glm::vec2(1.0f), glm::vec3(1.0f)});
                }
                mVertices.push_back(mVertices[0]);
                mVertices.push_back(Vertex{bezierPoints[29], glm::vec3(1.0f), glm::vec2(1.0f), glm::vec3(1.0f)});
                mVertices.push_back(vert);
                 bCurve2nd = false;
            }
            else
            {
                if (mVertices.size() >= 3)
                {
                    Vertex vert2 = mVertices[mVertices.size() - 1];
                    mVertices.push_back(mVertices[0]);
                    mVertices.push_back(vert2);
                    mVertices.push_back(vert);
                    bCurve2nd = false;
                }
                else
                {
                    mVertices.push_back(vert);
                    bCurve2nd = false;
                }
            }
        }

        glBindVertexArray(mVAO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, mLineVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * sizeof(float), &mLineVertices);

        bFirst = false;
        bPressed = false;
        bCurve = false;
    }
}

void Pen::OnMove(float xpos, float ypos, float xdelta, float ydelta)
{
    printf("%s", "  move  ");
    if (!bDraw)
        return;

    glm::vec3 point = ScreenToNDC(glm::vec2(xpos, ypos));

    if (bPressed)
    {
        if (glm::length(mNowPoint - point) < CURVE_DISTANCE)
        {
            bCurve = false;
            return;
        }

        bCurve = true;
        std::vector<glm::vec3> bezierPoints = bezierSpline(mNowPoint, point, mVertices[mVertices.size() - 1].Position, 30);
        for (int i = 0; i < 30; i++)
        {
            mSplineVertices[9 * i] = mVertices[0].Position.x;
            mSplineVertices[9 * i + 1] = mVertices[0].Position.y;
            mSplineVertices[9 * i + 2] = mVertices[0].Position.z;

            mSplineVertices[9 * i + 3] = bezierPoints[i].x;
            mSplineVertices[9 * i + 4] = bezierPoints[i].y;
            mSplineVertices[9 * i + 5] = bezierPoints[i].z;

            mSplineVertices[9 * i + 6] = bezierPoints[i + 1].x;
            mSplineVertices[9 * i + 7] = bezierPoints[i + 1].y;
            mSplineVertices[9 * i + 8] = bezierPoints[i + 1].z;
        }
        mSplineVertices[267] = mVertices[mVertices.size() - 1].Position.x;
        mSplineVertices[268] = mVertices[mVertices.size() - 1].Position.y;
        mSplineVertices[269] = mVertices[mVertices.size() - 1].Position.z;
    }
    else
    {
        if (bCurve2nd)
        {
            std::vector<glm::vec3> bezierPoints = bezierSpline(mVertices[mVertices.size() - 1].Position, mControlPoint1, point, 30);
            for (int i = 0; i < 30; i++)
            {
                mSplineVertices[9 * i] = mVertices[0].Position.x;
                mSplineVertices[9 * i + 1] = mVertices[0].Position.y;
                mSplineVertices[9 * i + 2] = mVertices[0].Position.z;

                mSplineVertices[9 * i + 3] = bezierPoints[i].x;
                mSplineVertices[9 * i + 4] = bezierPoints[i].y;
                mSplineVertices[9 * i + 5] = bezierPoints[i].z;

                mSplineVertices[9 * i + 6] = bezierPoints[i + 1].x;
                mSplineVertices[9 * i + 7] = bezierPoints[i + 1].y;
                mSplineVertices[9 * i + 8] = bezierPoints[i + 1].z;
            }
            mSplineVertices[267] = mVertices[0].Position.x;
            mSplineVertices[268] = mVertices[0].Position.y;
            mSplineVertices[269] = mVertices[0].Position.z;
        }
        else
        {
            mLineVertices[3] = point.x * PEN_SPEED;
            mLineVertices[4] = point.y * PEN_SPEED;
            mLineVertices[5] = point.z * PEN_SPEED;
        }
    }
}

std::vector<glm::vec3> Pen::bezierSpline(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, int pointNum)
{
    std::vector<glm::vec3> bezierPoint;
    bezierPoint.reserve(pointNum);

    float space = 1.0f / static_cast<float>(pointNum);
    for (int i = 0; i < pointNum; i++)
    {
        float ax = lerp(point1.x, point2.x, space * i);
        float ay = lerp(point1.y, point2.y, space * i);

        float bx = lerp(point2.x, point3.x, space * i);
        float by = lerp(point2.y, point3.y, space * i);

        float x = lerp(ax, bx, space * i);
        float y = lerp(ay, by, space * i);
        bezierPoint.push_back(glm::vec3(x, y, 0.0f));
    }

    return bezierPoint;
}