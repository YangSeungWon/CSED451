#include "Shell.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>

Shell::Shell(float _x, float _y) {
	x = _x;
	y = _y;
	dx = 2;
	dy = 5;
}

void Shell::display() {
	glColor3f(0.0f, 1.0f, 0.0f);
	glRectf(x - 1.0, y, x + 1.0, y + 2.0);
}

bool Shell::update() {
	x += dx;
	y += dy;
	dy -= 0.5;
	if (y < 25) {
		return false;
	}
	return true;
}