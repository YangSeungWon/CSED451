#pragma once
#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "constants.h"

void drawModel(std::vector< glm::vec3 > vertices, std::vector< glm::vec2 > uvs);
void drawCircle(float radius);
float radToDeg(float rad);
float degToRad(float deg);
void setColor(color _color);