#pragma once
#include <vector>
#include "Shell.h"
class Tank
{
private:
	float x = 50.0;
	float y = 25.0;
	std::vector<Shell*> shell;
public:
	void display();
	void goRight(float d);
	void goLeft(float d);
	void fire();
	void updateShell(int value);
};

