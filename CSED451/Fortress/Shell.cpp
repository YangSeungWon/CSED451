#include "Shell.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include "constant.h"

Shell::Shell(float _x, float _y) {
	x = _x;
	y = _y;
	dx = -2;
	dy = +2;
	radius = 1;
}

void Shell::display() {
	float angle;
	glColor3f(0.3f, 0.6f, 1.0f);

	glBegin(GL_POLYGON);
		for (angle = 0; angle < 2 * M_PI; angle += M_PI / 180) {
			glVertex2f(x + radius * cos(angle), y + RATIO * radius * sin(angle));
		}
	glEnd();
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