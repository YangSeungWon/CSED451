#pragma once
#include "Model.h"

class Ground
{
private:
	int width = 50;
	int height = 50;
	float interval = 5.0;
	static Model model;
public:
	Ground();
	void display();
};
