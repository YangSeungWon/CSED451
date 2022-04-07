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
#include "Model.h"

Model Head::model = Model("resources/head.obj");

void Head::display() {
	float angle;

	// crown
	setColor(duck->getColorCrown());
	model.display();

	glPushMatrix();
	beak.display();
	glPopMatrix();
}

void Head::fire() {
	beak.fire();
}

extern std::vector<Shell*> shells;
Model Beak::model = Model("resources/beak.obj");

void Beak::display() {
	glRotatef(radToDeg(angle), 0.0, 0.0, 1.0);
	glColor3f(0.9f, 0.9f - power * 0.10f, 0.3f);

	model.display();
}

void Beak::fire() {
	float x, y, offsetX, offsetY;
	x = y = 0;
	Duck* duck = head->getDuck();

	// duck
	x = duck->getX();
	y = duck->getY();

	// head
	offsetX = 5;
	offsetY = 14;
	x += offsetX;
	y += offsetY;

	// beak
	float radius = 8.5;
	offsetX = radius * cos(angle);
	offsetY = radius * sin(angle);
	x += offsetX;
	y += offsetY;

	float shell_angle = angle; // !

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
