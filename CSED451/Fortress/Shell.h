#pragma once
class Shell
{
private:
	float x;
	float y;
	float dx;
	float dy;
public:
	Shell(float x, float y);
	void display();
	bool update();
};

