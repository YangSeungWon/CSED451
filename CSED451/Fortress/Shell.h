#pragma once
class Shell
{
private:
	float x;
	float y;
	float dx;
public:
	float dy;
	Shell(float _x, float _y, float _angle, unsigned int _power);
	void display();
	bool update();
};

