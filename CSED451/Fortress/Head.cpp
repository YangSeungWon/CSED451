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
	setColor(duck->getColorBody());
	model.display();

	glPushMatrix();
	beak.display();
	glPopMatrix();
}

unsigned int Head::fire() {
	return beak.fire();
}

extern std::vector<Shell*> shells;
Model Beak::model = Model("resources/beak.obj");

void Beak::display() {
	glRotatef(radToDeg(angle), 0.0, 0.0, 1.0);
	glColor3f(0.9f, 0.9f - power * 0.10f, 0.3f);

	model.display();
}

glm::vec3 Beak::getPos() {
	glm::vec3 pos;
	Duck* duck = head->getDuck();

	// duck
	float duckAngle = duck->getAngle();

	// head
	pos = duck->getHeadPos();
	float headAngle = duck->getHeadAngle();

	// beak
	float radius = 15.0;
	pos += glm::vec3(
		radius * cos(degToRad(duckAngle + headAngle)) * cos(angle),
		radius * sin(angle),
		-radius * sin(degToRad(duckAngle + headAngle)) * cos(angle)
	);

	return pos;
}

unsigned int Beak::fire() {
	glm::vec3 pos, orientation;
	Duck* duck = head->getDuck();

	// duck
	float duckAngle = duck->getAngle();

	// head
	pos = duck->getHeadPos();
	float headAngle = duck->getHeadAngle();
	orientation = pos;

	// beak
	float radius = 15.0;
	pos += glm::vec3(
		radius * cos(degToRad(duckAngle + headAngle)) * cos(angle),
		radius * sin(angle),
		-radius * sin(degToRad(duckAngle + headAngle)) * cos(angle)
	);
	orientation = pos - orientation;

	Shell* new_shell = new Shell(pos, orientation * (float)power / radius);
	shells.push_back(new_shell);

	return power;
}

void Beak::increaseBeakAngle()
{
	angle += M_PI / 24;
	if (angle > M_PI / 6) {
		angle = M_PI / 6;
	}
}

void Beak::decreaseBeakAngle()
{
	angle -= M_PI / 24;
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
