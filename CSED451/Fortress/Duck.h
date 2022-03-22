#pragma once
#include "Head.h"
#include "Body.h"

class Duck
{
private:
	float x = 50.0;
	float y = 15.0;
	Head head;
	Body body;
public:
	void display();
	void goRight(float d);
	void goLeft(float d);
	void fire();
};