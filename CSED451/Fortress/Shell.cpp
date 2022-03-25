#include "Shell.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include "constants.h"
#include "utils.h"

Shell::Shell(float _x, float _y, float _angle, unsigned int _power) {
	x = _x;
	y = _y;
	dx = cos(_angle) * _power;
	dy = sin(_angle) * _power;
}

void Shell::display() {
	float angle;
	glColor3f(0.3f, 0.6f, 1.0f);
	glTranslatef(x, y, 0.0);
	drawCircle(1.0);
}

void Shell::update() {
	x += dx;
	y += dy;
	dy -= 0.5;
}