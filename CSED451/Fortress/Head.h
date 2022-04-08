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
	static Model model;
public:
	Beak(Head* _head) : head{ _head } {
		model.load();
	}
	void display();
	unsigned int fire();
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
	static Model model;
public:
	Head(Duck* _duck) : duck{ _duck }, beak{ this } {
		model.load();
	}
	Duck* getDuck() { return duck; }
	void display();
	unsigned int fire();
	void increaseBeakAngle() { beak.increaseBeakAngle(); }
	void decreaseBeakAngle() { beak.decreaseBeakAngle(); }
	void increaseBeakPower() { beak.increaseBeakPower(); }
	void decreaseBeakPower() { beak.decreaseBeakPower(); }
};