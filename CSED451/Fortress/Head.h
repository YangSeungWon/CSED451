#pragma once
#include <iostream>
#include <vector>

class Duck;
class Head;
class Shell;

class Beak
{
private:
	Head* head;
	std::vector<Shell*> shell;
public:
	void display();
	Beak(Head* _head) : head{ _head }, shell{std::vector<Shell*>()} {}
	void fire();
	void updateShell(int value);
};

class Head
{
private:
	Duck* duck;
	Beak beak;
	float radius = 5;
	float offsetX = -5;
	float offsetY = 21;
public:
	Head(Duck* _duck) : duck{ _duck }, beak{ Beak(this) } {  }
	float getX();
	float getY();
	float getRadius() { return radius; }
	void display();
	void fire();
	void updateShell(int value);
};