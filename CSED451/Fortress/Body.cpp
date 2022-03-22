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

void Body::display() {
	float angle;

	glColor3f(0.2f, 0.2f, 0.2f);

	// body
	glBegin(GL_POLYGON);
		for (angle = 2 * M_PI + M_PI * 0.2; angle > M_PI - M_PI * 0.2; angle -= M_PI / 180) {
			glVertex2f(10.0 * cos(angle), 6.7 * sin(angle));
		}
	glEnd();

	// tail
	glPushMatrix();
	glBegin(GL_POLYGON);
		float last_angle = 2 * M_PI + M_PI * 0.2;
		glVertex2f(-10.0, 0.0);
		glVertex2f(-10.0, 4.7);
		glVertex2f(-10.0 * cos(last_angle), 6.7 * sin(last_angle));
	glEnd();
	glPopMatrix();

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

void Wheel::display() {
	glRotatef(radToDeg(angle), 0.0, 0.0, 1.0);
	glColor3f(0.9f, 0.65f, 0.3f);

	glBegin(GL_POLYGON);
		glVertex2f(0.0, 0.0);
		glVertex2f(-2.0, -3.7);
		glVertex2f(0.0, -5.3);
		glVertex2f(2.0, -3.7);
	glEnd();
}