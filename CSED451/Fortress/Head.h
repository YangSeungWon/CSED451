#pragma once
#include <iostream>
#include <vector>
#include "constants.h"
#include <glm/glm.hpp>
#include "Model.h"

class Duck;
class Head;
class Shell;

class Beak
{
private:
	float angle = M_PI / 12;
	unsigned int power = 3;
	Head* head;
public:
	Beak(Head* _head) : head{ _head } {}
	static Model model;
	void display(glm::mat4 modelmtx, glm::mat4 projmtx);
	unsigned int fire();
	float getAngle() { return angle; }
	glm::vec3 getPos();
	glm::vec3 getOrientation();
	void increaseBeakAngle();
	void decreaseBeakAngle();
	void increaseBeakPower();
	void decreaseBeakPower();
};

class Head
{
private:
	Beak beak;
	Duck* duck;
public:
	Head(Duck* _duck) : duck{ _duck }, beak{ this } {}
	static Model model;
	Duck* getDuck() { return duck; }
	void display(glm::mat4 modelmtx, glm::mat4 projmtx);
	unsigned int fire();
	glm::vec3 getBeakPos() { return beak.getPos(); }
	void increaseBeakAngle() { beak.increaseBeakAngle(); }
	void decreaseBeakAngle() { beak.decreaseBeakAngle(); }
	void increaseBeakPower() { beak.increaseBeakPower(); }
	void decreaseBeakPower() { beak.decreaseBeakPower(); }
};