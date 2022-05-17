#include "Head.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <windows.h>
#include <algorithm>
#include "Shell.h"
#include "Duck.h"
#include "constants.h"
#include "utils.h"
#include "Model.h"

Model Head::model = Model("resources/head.obj", texture_t::DUCK);

void Head::display(glm::mat4 modelmtx, glm::mat4 projmtx) {
	glm::vec4 color4 = getColor(duck->getColorBody());
	model.display(color4, modelmtx, projmtx);
	beak.display(modelmtx, projmtx);
}

unsigned int Head::fire() {
	return beak.fire();
}

extern std::vector<Shell*> shells;
Model Beak::model = Model("resources/beak.obj", texture_t::DUCK);

void Beak::display(glm::mat4 modelmtx, glm::mat4 projmtx) {
	glm::mat4 beakModelmtx = modelmtx;
	beakModelmtx = glm::rotate(beakModelmtx, angle, glm::vec3(0.0, 0.0, 1.0));
	glm::vec4 color = glm::vec4(0.9f, 0.9f - power * 0.10f, 0.3f, 1.0f);
	model.display(color, beakModelmtx, projmtx);
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
