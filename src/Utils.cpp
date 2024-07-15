#include "Utils.h"

glm::vec3 ScreenToNDC(glm::vec2 screen){

    glm::vec4 ndcCoord;
    ndcCoord.x = (2.0f * screen.x) / SCR_WIDTH - 1.0f;
    ndcCoord.y = 1.0f - (2.0f *screen.y) / SCR_HEIGHT;
    ndcCoord.z = 0.0f-1.0f;
    ndcCoord.w = 1.0f;
    return  glm::vec3(ndcCoord.x,ndcCoord.y,0.0f);
}

glm::vec2 NDCToScreen(glm::vec2 ndc){
    glm::vec2 screen;
    screen.x = (ndc.x+1)*0.5f*SCR_WIDTH;
    screen.y = (ndc.y+1)*0.5f*SCR_HEIGHT;
    return screen;
}