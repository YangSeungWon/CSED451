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
	for (int i = 0; i < 2; i++) {
		glPushMatrix();
		glTranslatef(-11.0, -4.0, -8.0 + i * 16.0);
		for (int j = 0; j < NUM_WHEELS; j++) {
			glPushMatrix();
			glTranslatef(11.0 * j, 0.0, 0.0);
			wheels[j].display();
			glPopMatrix();
		}
		glPopMatrix();
	}
}

void Body::rotateWheel() {
	bool isForward = duck->getForward();
	for (int i = 0; i < NUM_WHEELS; i++) {
		wheels[i].increaseAngle(
			isForward ? -(M_PI / 6) : (M_PI / 6)
		);
	}
}

Model Wheel::model = Model("resources/wheel.obj");

void Wheel::display() {
	glRotatef(radToDeg(angle), 0.0, 0.0, 1.0);
	glColor3f(0.9f, 0.65f, 0.3f);

	model.display();
}