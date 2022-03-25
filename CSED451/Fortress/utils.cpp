#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include "constants.h"
#include "utils.h"

void drawCircle(float radius) {
	float angle;
	glBegin(GL_POLYGON);
	for (angle = 0; angle < 2 * M_PI; angle += M_PI / 180) {
		glVertex2f(radius * cos(angle), radius * sin(angle));
	}
	glEnd();
}

float radToDeg(float rad) {
	return rad / M_PI * 180;
}

float degToRad(float deg) {
	return deg / 180 * M_PI;
}

void setColor(color _color) {
	switch (_color) {
	case color::BLACK:
		glColor3f(0.2f, 0.2f, 0.2f);
		break;
	case color::BLUE:
		glColor3f(0.0f, 0.6f, 0.9f);
		break;
	case color::BEIGE:
		glColor3f(0.9f, 0.8f, 0.7f);
		break;
	case color::PINK:
		glColor3f(1.0f, 0.6f, 0.6f);
		break;
	case color::SKYBLUE:
		glColor3f(0.5f, 0.8f, 1.0f);
		break;
	case color::LIGHTSKYBLUE:
		glColor3f(0.8f, 0.95f, 1.0f);
		break;
	case color::WHITE:
		glColor3f(1.0f, 1.0f, 1.0f);
		break;
	case color::YELLOW:
		glColor3f(0.9f, 0.65f, 0.3f);
		break;
	}
}