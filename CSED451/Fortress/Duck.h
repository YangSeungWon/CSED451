#pragma once
#include "Head.h"
#include "Body.h"
#include "constants.h"

class Duck
{
private:
	float x;
	float y = 15.0;
	Head head;
	Body body;
	ori_t orientation;
public:
	Duck(float _x, ori_t _orientation) : head{ this }, body{}, 
		x{ _x }, orientation{ _orientation } {}
	void display();
	void goRight(float d);
	void goLeft(float d);
	void fire();
	float getX() { return x; }
	float getY() { return y; }
	ori_t getOrientation() { return (ori_t)orientation; }
	void increaseBeakAngle() { head.increaseBeakAngle(); }
	void decreaseBeakAngle() { head.decreaseBeakAngle(); }
	void increaseBeakPower() { head.increaseBeakPower(); }
	void decreaseBeakPower() { head.decreaseBeakPower(); }
};