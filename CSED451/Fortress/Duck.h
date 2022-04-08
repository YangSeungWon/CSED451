#pragma once
#include <glm/vec3.hpp>
#include "Head.h"
#include "Body.h"
#include "constants.h"

class Duck
{
private:
	glm::vec3 pos;
	float angle;
	bool isForward = true;

	// Recoil
	bool isRecoil = false;
	float lastFireTime = 0.0f;
	unsigned int lastFirePower = 0;
	float displacement;
	float velocity;

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
		pos{ glm::vec3(_x, _y, _z) }, angle{ _angle },
		color_body{ _color_body }, color_crown{ _color_crown } {}
	void display();
	void cageInBoundary();
	void goForward(float d);
	void goBack(float d);
	void goDown(float d);
	void fire();
	void recoil();
	glm::vec3 getPos() { return pos; }
	float getAngle() { return angle; }
	float getHeadAngle() { return headAngle; }
	glm::vec3 getHeadPos();
	glm::vec3 getBeakPos() { return head.getBeakPos(); }
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