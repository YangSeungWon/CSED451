#pragma once
#include "Shell.h"
#include "Head.h"
#include "Body.h"

class Duck
{
private:
	float x = 50.0;
	float y = 25.0;
	Head head;
	Body body;
public:
	Duck();
	float getX() { return x; }
	float getY() { return y; }
	void display();
	void goRight(float d);
	void goLeft(float d);
	void fire();
	void updateShell(int value);
};