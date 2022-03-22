#include "Head.h"
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

void Head::display() {
	float angle;

	// crown
	glColor3f(0.0f, 0.6f, 0.9f);
	glBegin(GL_POLYGON);
		glVertex2f(0.0, 4.5);
		glVertex2f(2.0, 6.5);
		glVertex2f(3.0, 4.5);
		glVertex2f(5.0, 5.5);
		glVertex2f(5.0, 3.5);
		glVertex2f(7.0, 2.0);
		glVertex2f(5.0, 0.0);
	glEnd();

	// head
	glColor3f(0.2f, 0.2f, 0.2f);
	drawCircle(5.0);

	// eye
	glPushMatrix();
	glTranslatef(-1.0, 2.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawCircle(1.5);
	glPopMatrix();

	// pupil
	glPushMatrix();
	glTranslatef(-1.3, 2.7, 0.0);
	glColor3f(0.0f, 0.6f, 0.9f);
	drawCircle(1.0);
	glPopMatrix();

	// beak
	glPushMatrix();
	beak.display();
	glPopMatrix();
}

void Head::fire() {
	beak.fire();
}


extern std::vector<Shell*> shells;

void Beak::display() {
	glColor3f(0.9f, 0.75f, 0.3f);
	GLfloat matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	for (int i = 0; i < 16; i += 1) {
		std::cout << "display " << i << matrix[i] << '\n';
	}

	glBegin(GL_POLYGON);
		glVertex2f(-3.0, 4.0);
		glVertex2f(-5.0, -0.0);
		glVertex2f(-7.5, 4.3);
	glEnd();
}

void Beak::fire() {
	GLfloat matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	for (int i = 0; i < 16; i += 1) {
		std::cout << i << matrix[i] << '\n';
	}
	Shell* new_shell = new Shell(matrix[0]*4500, matrix[5]*3000, angle, power);
	shells.push_back(new_shell);
}
