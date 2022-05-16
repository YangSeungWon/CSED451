#pragma once
#include "glm/mat4x4.hpp"
#include "Model.h"
#include "constants.h"

class Ground
{
private:
	float interval = 80.0;
	int width = GROUND_BOUNDARY / interval * 2;
	int height = GROUND_BOUNDARY / interval * 2;
	static Model model;
public:
	Ground();
	void display(glm::mat4 modelmtx, glm::mat4 projmtx);
};
