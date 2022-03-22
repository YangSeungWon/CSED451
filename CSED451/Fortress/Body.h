#pragma once

#define NUM_WHEELS 5

class Wheel
{
private:
public:
	void display();
};

class Body
{
private:
	Wheel wheels[NUM_WHEELS];
public:
	void display();
};
