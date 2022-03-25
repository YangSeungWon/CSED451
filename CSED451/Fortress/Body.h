#pragma once

#define NUM_WHEELS 5

class Duck;

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
	Duck* duck;
public:
	Body(Duck* _duck) : duck{ _duck } {}
	void display();
	void rotateWheel();
};
