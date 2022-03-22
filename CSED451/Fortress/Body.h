#pragma once

#define NUM_WHEELS 5

class Wheel
{
private:
	float angle = 0;
public:
	void display();
	void increaseAngle(float _angle) { angle += _angle; }
};

class Body
{
private:
	Wheel wheels[NUM_WHEELS];
public:
	void display();
	void rotateWheel();
};
