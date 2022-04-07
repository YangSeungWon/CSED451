#pragma once

#define NUM_WHEELS 5

#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "Model.h"

class Duck;

class Wheel
{
private:
	float angle = 0;
	static Model model;
public:
	Wheel() {
		model.load();
	}
	void display();
	void increaseAngle(float _angle) { angle += _angle; }
};

class Body
{
private:
	Wheel wheels[NUM_WHEELS];
	Duck* duck;
	static Model model;
public:
	Body(Duck* _duck) : duck{ _duck } {
		model.load();
	}
	void display();
	void rotateWheel();
};
