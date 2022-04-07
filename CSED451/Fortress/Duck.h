#pragma once
#include "Head.h"
#include "Body.h"
#include "constants.h"

class Duck
{
private:
	float x;
	float y;
	float z;
	float angle;
	bool isForward = true;
	Head head;
	Body body;
	float headAngle = 0.0;
	color color_body;
	color color_crown;
	int life = 3;
public:
	static float crash_radius;
	Duck(color _color_body, color _color_crown, 
		float _x, float _y, float _z, float _angle) 
		: head{ this }, body{ this },
		x{ _x }, y{ _y }, z{ _z }, angle{ _angle },
		color_body{ _color_body }, color_crown{ _color_crown } {}
	void display();
	void goForward(float d);
	void goBack(float d);
	void goDown(float d);
	void fire();
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	void setForward(bool _isForward) { isForward = _isForward; }
	bool getForward() { return isForward; }
	void rotate(float _angle) { angle += _angle; }
	int getLife() { return life; }
	color getColorBody() { return color_body; }
	color getColorCrown() { return color_crown; }
	void rotateHead(float _angle);
	void increaseBeakAngle() { head.increaseBeakAngle(); }
	void decreaseBeakAngle() { head.decreaseBeakAngle(); }
	void increaseBeakPower() { head.increaseBeakPower(); }
	void decreaseBeakPower() { head.decreaseBeakPower(); }
	bool strike(int power);
};