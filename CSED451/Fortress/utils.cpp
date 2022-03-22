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