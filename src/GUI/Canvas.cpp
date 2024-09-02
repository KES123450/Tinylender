#include "Canvas.h"

void Canvas::Rendering()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for (auto const &child : mChild)
    {
        if (child->GetVisible())
        {
            child->Draw();
        }
    }
}

void Canvas::AddWidget(Widget *w)
{
    mChild.push_back(w);
}

void Canvas::OnPointerUp(float xpos, float ypos, float xdelta, float ydelta)
{
    float ndcX = (2 * xpos / SCR_WIDTH) - 1;
    float ndcY = 1 - (2 * ypos / SCR_HEIGHT);

    for (Widget *child : mChild)
    {
        if (child->GetType() != eUIType::BUTTON)
            continue;
        Button *b = static_cast<Button *>(child);
        glm::vec3 pos = b->GetPos();
        glm::vec2 size = b->GetSize();
        glm::vec2 sizeHalf = glm::vec2(size.x / 2, size.y / 2);

        if (ndcX >= (pos.x - sizeHalf.x) && ndcX <= (pos.x + sizeHalf.x) && ndcY >= (pos.y - sizeHalf.y) && ndcY <= (pos.y + sizeHalf.y))
        {
            if (b->getButtonCallback() != NULL)
                b->Callbtn();
        }
    }
}
