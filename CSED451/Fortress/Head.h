#pragma once
#include <iostream>
#include <vector>
#include "constants.h"
#include <glm/glm.hpp>
#include "objloader.h"

class Duck;
class Head;
class Shell;

class Beak
{
private:
	float angle = M_PI / 4;
	unsigned int power = 3;
	Head* head;
public:
	Beak(Head* _head) : head{ _head } {}
	void display();
	void fire();
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
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;
public:
	Head(Duck* _duck) : duck{ _duck }, beak{ this } {
		bool res = loadOBJ("resources/head.obj", vertices, uvs, normals);
	}
	Duck* getDuck() { return duck; }
	void display();
	void fire();
	void increaseBeakAngle() { beak.increaseBeakAngle(); }
	void decreaseBeakAngle() { beak.decreaseBeakAngle(); }
	void increaseBeakPower() { beak.increaseBeakPower(); }
	void decreaseBeakPower() { beak.decreaseBeakPower(); }
};