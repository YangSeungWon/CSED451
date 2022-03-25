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
	setColor(duck->getColorCrown());
	glBegin(GL_POLYGON);
		glVertex2f(0.0, 4.5);
		glVertex2f(-2.0, 6.5);
		glVertex2f(-3.0, 4.5);
		glVertex2f(-5.0, 5.5);
		glVertex2f(-5.0, 3.5);
		glVertex2f(-7.0, 2.0);
		glVertex2f(-5.0, 0.0);
	glEnd();

	// head
	setColor(duck->getColorBody());
	drawCircle(5.0);

	// eye
	glPushMatrix();
	glTranslatef(1.0, 2.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawCircle(1.5);
	glPopMatrix();

	// pupil
	glPushMatrix();
	glTranslatef(1.3, 2.7, 0.0);
	setColor(duck->getColorCrown());
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
	glRotatef(radToDeg(angle), 0.0, 0.0, 1.0);
	glColor3f(0.9f, 0.9f - power * 0.10f, 0.3f);

	glBegin(GL_POLYGON);
		glVertex2f(4.5, 2.0);
		glVertex2f(4.5, -2.0);
		glVertex2f(8.5, 0.0);
	glEnd();
}

void Beak::fire() {
	float x, y, offsetX, offsetY;
	x = y = 0;
	Duck* duck = head->getDuck();

	// duck
	x = duck->getX();
	y = duck->getY();
	ori_t orientation = duck->getOrientation();

	// head
	offsetX = 5;
	offsetY = 14;
	if (orientation == ori_t::LEFT) {
		offsetX *= -1;
	}
	x += offsetX;
	y += offsetY;

	// beak
	float radius = 8.5;
	offsetX = radius * cos(angle);
	offsetY = radius * sin(angle);
	if (orientation == ori_t::LEFT) {
		offsetX *= -1;
	}
	x += offsetX;
	y += offsetY;

	float shell_angle = angle;
	if (orientation == ori_t::LEFT) {
		shell_angle = -shell_angle + M_PI;
	}

	Shell* new_shell = new Shell(x, y, shell_angle, power);
	shells.push_back(new_shell);
}

void Beak::increaseBeakAngle()
{
	angle += M_PI / 12;
	if (angle > M_PI / 2) {
		angle = M_PI / 2;
	}
}

void Beak::decreaseBeakAngle()
{
	angle -= M_PI / 12;
	if (angle < 0) {
		angle = 0;
	}
}

void Beak::increaseBeakPower()
{
	power++;
	if (power > 5) {
		power = 5;
	}
}

void Beak::decreaseBeakPower()
{
	power--;
	if (power < 1) {
		power = 1;
	}
}
