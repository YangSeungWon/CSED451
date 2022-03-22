#pragma once
#include <iostream>
#include <vector>
#include "constants.h"

class Duck;
class Head;
class Shell;

class Beak
{
private:
	float angle = M_PI / 4;
	unsigned int power = 3;
public:
	void display();
	void fire();
};

class Head
{
private:
	Beak beak;
public:
	void display();
	void fire();
};