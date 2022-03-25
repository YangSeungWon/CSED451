#pragma once
class Shell
{
private:
	float x;
	float y;
	float dx;
	float dy;
public:
	Shell(float _x, float _y, float _angle, unsigned int _power);
	float getX() { return x; }
	float getY() { return y; }
	void display();
	void update();
};

