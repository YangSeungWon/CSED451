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
#include "constant.h"


Body::Body(Duck* _duck)
	: duck{ _duck }
	, feet{ Foot(this, -3.0), Foot(this, 3.0) }{
}

float Body::getX() { return duck->getX() + offsetX; }
float Body::getY() { return duck->getY() + offsetY; }

void Body::display() {
	//feet
	feet[0].display();
	feet[1].display();

	float x = duck->getX() + offsetX;
	float y = duck->getY() + offsetY;
	float angle;

	glColor3f(0.2f, 0.2f, 0.2f);

	// body
	glBegin(GL_POLYGON);
		for (angle = M_PI - M_PI * 0.2; angle < 2 * M_PI + M_PI * 0.2; angle += M_PI / 180) {
			glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
		}
	glEnd();

	// tail
	glBegin(GL_POLYGON);
		float last_angle = 2 * M_PI + M_PI * 0.2;
		glVertex2f(x + radius, y);
		glVertex2f(x + radius, y + 7.0);
		glVertex2f(x + radius * cos(last_angle), y + radius * sin(last_angle));
	glEnd();
}


void Foot::display() {
	glColor3f(0.9f, 0.65f, 0.3f);

	float radius = body->getRadius();
	float x = body->getX() + offsetX;
	float y = body->getY() - radius + 2.0;

	glBegin(GL_POLYGON);
	glVertex2f(x + 0.0 * radius, y + 0.0 * radius);
	glVertex2f(x - 0.2 * radius, y - 0.55 * radius);
	glVertex2f(x + 0.0 * radius, y - 0.8 * radius);
	glVertex2f(x + 0.2 * radius, y - 0.55 * radius);
	glEnd();
}