#pragma once
#include "Model.h"
#include "constants.h"

class Ground
{
private:
	float interval = 5.0;
	int width = GROUND_BOUNDARY / interval * 2;
	int height = GROUND_BOUNDARY / interval * 2;
	static Model model;
public:
	Ground();
	void display();
};
