#include "Shell.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include "constants.h"
#include "utils.h"

Shell::Shell(glm::vec3 _pos, glm::vec3 _velocity) {
	pos = _pos;
	velocity = _velocity;
}

void Shell::display() {
	float angle;
	glColor3f(0.3f, 0.6f, 1.0f);
	glTranslatef(pos.x, pos.y, pos.z);
	glutWireSphere(3.0, 5, 10);
}

void Shell::update() {
	pos += velocity;
	velocity.y -= 0.5;
}