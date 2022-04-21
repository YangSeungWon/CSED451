#pragma once

#define NUM_WHEELS 3
#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "Model.h"

class Duck;

class Wheel
{
private:
	float angle = 0;
public:
	Wheel() {}
	static Model model;
	void display(glm::mat4 modelmtx, glm::mat4 projmtx);
	void increaseAngle(float _angle) { angle += _angle; }
};

class Body
{
private:
	Wheel wheels[2 * NUM_WHEELS];
	Duck* duck;
public:
	Body(Duck* _duck) : duck{ _duck } {}
	static Model model;
	static Model lifemodel;
	void display(glm::mat4 modelmtx, glm::mat4 projmtx);
	void rotateWheel();
};
