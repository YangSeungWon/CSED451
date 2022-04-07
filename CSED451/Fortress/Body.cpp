#include "Body.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include <windows.h>
#include <algorithm>
#include "Shell.h"
#include "Duck.h"
#include "constants.h"
#include "utils.h"

Model Body::model = Model("resources/body.obj");

void Body::display() {
	float angle;

	setColor(duck->getColorBody());

	// body
	model.display();

	//wheels
	for (int i = 0; i < NUM_WHEELS; i++) {
		glPushMatrix();
		glTranslatef(-8.0 + 4.0 * i, -6.0, 0.0);
		wheels[i].display();
		glPopMatrix();
	}
}

void Body::rotateWheel() {
	for (int i = 0; i < NUM_WHEELS; i++) {
		wheels[i].increaseAngle(-M_PI / 6);
	}
}

Model Wheel::model = Model("resources/wheel.obj");

void Wheel::display() {
	glRotatef(radToDeg(angle), 0.0, 0.0, 1.0);
	glColor3f(0.9f, 0.65f, 0.3f);

	model.display();
}