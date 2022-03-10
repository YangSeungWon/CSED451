#pragma once

class Duck;
class Body;

class Foot
{
private:
	Body* body;
	float offsetX;
public:
	void display();
	Foot(Body* _body, float _offsetX) : body{ _body }, offsetX{ _offsetX } {}
};

class Body
{
private:
	Duck* duck;
	Foot feet[2];
	float radius = 10;
	float offsetX = 0;
	float offsetY = radius;
public:
	Body(Duck* _duck);
	float getX();
	float getY();
	void display();
	float getRadius() { return radius; }
};
