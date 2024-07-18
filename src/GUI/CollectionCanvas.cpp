#include "CollectionCanvas.h"
#include "../Collection.h"

CollectionCanvas::CollectionCanvas()
{
    mMaskShader = new Shader("Shader/UIVertexShader.glsl", "Shader/maskFragShader.glsl");
    Collection *collection = Collection::GetInstance();
    glm::vec3 layerUIPos = glm::vec3(-0.8510978043912175f, 0.8338536585365853f, 0.0f);
    mRootLayerUI = new LayerUI(collection->GetRootLayer(), 0.08351219512195122f, 0.0f, layerUIPos);

    glm::vec3 vertex[4];
    vertex[0] = glm::vec3(-1.0f, 1.0f - mLayerOffsetY, 0.0f); // 1 3
    vertex[1] = glm::vec3(-1.0f, -1.0f, 0.0f);                // 2 4
    vertex[2] = glm::vec3(-1 + mLayerSizeX, 1.0f - mLayerOffsetY, 0.0f);
    vertex[3] = glm::vec3(-1 + mLayerSizeX, -1.0f, 0.0f);

    glm::vec2 texCoord[4];
    texCoord[0] = glm::vec2(0.0f, 1.0f);
    texCoord[1] = glm::vec2(0.0f, 0.0f);
    texCoord[2] = glm::vec2(1.0f, 1.0f);
    texCoord[3] = glm::vec2(1.0f, 0.0f);

    float maskVertex[20] = {
        0.0f,
    };
    for (int i = 0; i < 4; i++)
    {
        maskVertex[i * 5 + 0] = vertex[i].x;
        maskVertex[i * 5 + 1] = vertex[i].y;
        maskVertex[i * 5 + 2] = vertex[i].z;
        maskVertex[i * 5 + 3] = texCoord[i].x;
        maskVertex[i * 5 + 4] = texCoord[i].y;
    }

    glGenBuffers(1, &mMaskVBO);
    glGenVertexArrays(1, &mMaskVAO);
    glGenBuffers(1, &mMaskEBO);

    glBindVertexArray(mMaskVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mMaskVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(maskVertex), maskVertex, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mMaskEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mMaskIndices), mMaskIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void CollectionCanvas::Rendering()
{
    glEnable(GL_STENCIL_TEST);
    glDisable(GL_DEPTH_TEST);
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    drawMask();

    glEnable(GL_DEPTH_TEST);
    glStencilMask(0x00);
    glStencilFunc(GL_EQUAL, 1, 0xFF);

    RenderingLayer(mRootLayerUI);

    glStencilFunc(GL_ALWAYS, 0, 0xFF); // Restore default stencil function
    glStencilMask(0xFF);
    glEnable(GL_DEPTH_TEST);
}

void CollectionCanvas::RenderingLayer(LayerUI *layer, int depth, int count)
{
    layer->Draw();

    if (layer->children.size() == 0)
        return;

    int c = 0;
    for (LayerUI *child : mRootLayerUI->children)
    {
        RenderingLayer(child, depth + 1, c);
        c++;
    }
}

void CollectionCanvas::AddLayerUI(Layer *layer)
{
    mCount = 1;
    int nodeCount = countNodes(mRootLayerUI);
    glm::vec3 layerUIPos = glm::vec3(-1 + mLayerSizeX / 2, 1 - mLayerOffsetY + (-mLayerSizeY) * nodeCount + (-mLayerSizeY / 2) + mScrollDiscanceY, 0.0f);
    LayerUI *ui = new LayerUI(layer, mLayerSizeX, mLayerSizeY, layerUIPos);
    mRootLayerUI->children.push_back(ui);
}

void CollectionCanvas::OnPointerDown(float xpos, float ypos, float xdelta, float ydelta)
{
    float ndcX = (2 * xpos / SCR_WIDTH) - 1;
    float ndcY = 1 - (2 * ypos / SCR_HEIGHT);

    if (ndcX >= -1 + mLayerSizeX || ndcY >= 1 - mLayerOffsetY)
        return;

    mCount = 0;
    int selectedLayerIndex = findLayer(ndcY, mRootLayerUI);
    if (selectedLayerIndex == -1)
        return;

    if (mPrevSelectedLayerUI != nullptr)
    {
        mPrevSelectedLayerUI->UnSelectLayerUI();
    }

    mCount = selectedLayerIndex;
    LayerUI *selectedLayerUI = findLayer(mRootLayerUI);
    selectedLayerUI->SelectLayerUI();
    Collection::GetInstance()->SelectLayer(selectedLayerUI->GetLayer());
    mPrevSelectedLayerUI = selectedLayerUI;
}

void CollectionCanvas::OnPointer(float xpos, float ypos, float xdelta, float ydelta)
{
}

void CollectionCanvas::OnPointerUp(float xpos, float ypos, float xdelta, float ydelta)
{
}

void CollectionCanvas::OnScroll(float xoffset, float yoffset)
{
    float scrollDistanceTest = (mScrollDiscanceY + -yoffset * SCROLL_SPEED) * SCR_HEIGHT;
    float layerLength = (LAYER_SIZE_Y / 2) * SCR_HEIGHT * (countNodes(mRootLayerUI) + 1);

    if (layerLength < SCR_HEIGHT - mLayerOffsetY * SCR_HEIGHT || abs(scrollDistanceTest) >= layerLength - SCR_HEIGHT || scrollDistanceTest <= 0)
        return;

    ScrollLayer(mRootLayerUI, xoffset, -yoffset);
    mScrollDiscanceY += -yoffset * SCROLL_SPEED;
}

int CollectionCanvas::findLayer(float yPos, LayerUI *layer)
{
    mCount++;

    if (yPos <= (layer->GetPos().y + layer->GetSize().y / 2) && yPos >= (layer->GetPos().y - layer->GetSize().y / 2))
        return mCount;

    for (LayerUI *child : layer->children)
    {
        int result = findLayer(yPos, child);
        if (result != -1)
        {
            return result;
        }
    }

    return -1;
}

LayerUI *CollectionCanvas::findLayer(LayerUI *layerUI)
{
    mCount--;
    if (mCount == 0)
    {
        return layerUI;
    }

    for (LayerUI *child : layerUI->children)
    {
        LayerUI *findLayerUI = findLayer(child);
        if (findLayerUI != nullptr)
            return findLayerUI;
    }
    return nullptr;
}

int CollectionCanvas::countNodes(LayerUI *layer)
{
    if (layer == nullptr)
        return 0;

    int count = 1;
    for (LayerUI *child : layer->children)
    {
        count += countNodes(child);
    }

    return count;
}

void CollectionCanvas::ScrollLayer(LayerUI *layer, float xoffset, float yoffset, int depth, int count)
{
    layer->ScrollLayerUI(xoffset, yoffset);

    if (layer->children.size() == 0)
        return;

    int c = 0;
    for (LayerUI *child : mRootLayerUI->children)
    {
        ScrollLayer(child, xoffset, yoffset, depth + 1, c);
        c++;
    }
}

void CollectionCanvas::drawMask()
{
    mMaskShader->use();
    // glStencilFunc(GL_ALWAYS, 1, 0xFF);
    // glStencilMask(0xFF);
    glBindVertexArray(mMaskVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
