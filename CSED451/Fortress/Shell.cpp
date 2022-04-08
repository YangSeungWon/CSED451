#include "Shell.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include "constants.h"
#include "utils.h"

extern bool hiddenLineRemoval;

Shell::Shell(glm::vec3 _pos, glm::vec3 _velocity) {
	pos = _pos;
	velocity = _velocity;
}

void Shell::display() {
	float angle;
	setColor(color::GREEN);
	glTranslatef(pos.x, pos.y, pos.z);
	glutWireSphere(3.0, 5, 10);

	if (hiddenLineRemoval) {
		setColor(color::DARKGRAY);
		glPushMatrix();
		glScalef(0.99, 0.99, 0.99);
		glutSolidSphere(3.0, 5, 10);
		glPopMatrix();
	}
}

void Shell::update() {
	pos += velocity;
	velocity.y -= 0.5;
}