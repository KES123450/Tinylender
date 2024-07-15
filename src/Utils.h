#pragma once

#include <glm/glm.hpp>
#include "constants.h"

glm::vec3 ScreenToNDC(glm::vec2 screen);
glm::vec2 NDCToScreen(glm::vec2 ndc);