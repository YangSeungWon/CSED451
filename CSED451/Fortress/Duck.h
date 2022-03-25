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
	color color_body;
	color color_crown;
	int life = 3;
public:
	static float crash_radius;
	Duck(color _color_body, color _color_crown, float _x, ori_t _orientation) 
		: head{ this }, body{ this },
		x{ _x }, orientation{ _orientation }, 
		color_body{ _color_body }, color_crown{ _color_crown } {}
	void display();
	void goRight(float d);
	void goLeft(float d);
	void backRight(float d);
	void backLeft(float d);
	void goDown(float d);
	void fire();
	float getX() { return x; }
	float getY() { return y; }
	ori_t getOrientation() { return (ori_t)orientation; }
	int getLife() { return life; }
	color getColorBody() { return color_body; }
	color getColorCrown() { return color_crown; }
	void increaseBeakAngle() { head.increaseBeakAngle(); }
	void decreaseBeakAngle() { head.decreaseBeakAngle(); }
	void increaseBeakPower() { head.increaseBeakPower(); }
	void decreaseBeakPower() { head.decreaseBeakPower(); }
	bool strike();
};