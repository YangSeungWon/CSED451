#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec4.hpp>
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

glm::vec4 getColor(color _color) {
	switch (_color) {
	case color::BLACK:
		return glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	case color::DARKGRAY:
		return glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
	case color::BLUE:
		return glm::vec4(0.0f, 0.6f, 0.9f, 1.0f);
	case color::BEIGE:
		return glm::vec4(0.9f, 0.8f, 0.7f, 1.0f);
	case color::PINK:
		return glm::vec4(1.0f, 0.6f, 0.6f, 1.0f);
	case color::SKYBLUE:
		return glm::vec4(0.5f, 0.8f, 1.0f, 1.0f);
	case color::LIGHTSKYBLUE:
		return glm::vec4(0.8f, 0.95f, 1.0f, 1.0f);
	case color::WHITE:
		return glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	case color::YELLOW:
		return glm::vec4(0.9f, 0.65f, 0.3f, 1.0f);
	case color::LIGHTGRAY:
		return glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
	case color::GREEN:
		return glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	}
}