#include "Body.h"
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

extern bool hiddenLineRemoval;
extern unsigned int ID;

Model Body::model = Model("resources/body.obj", texture_t::DUCK);
Model Body::lifemodel = Model("resources/life.obj", texture_t::SHELL);

void Body::display(glm::mat4 modelmtx, glm::mat4 projmtx) {
	// body
	glm::vec4 color4 = getColor(duck->getColorBody());
	model.display(color4, modelmtx, projmtx);

	//wheels
	glm::mat4 wheelModelmtx;
	for (int i = 0; i < 2; i++) {
		wheelModelmtx = glm::translate(modelmtx, glm::vec3(-11.0, -4.0, -8.0 + i * 16.0));
		for (int j = 0; j < NUM_WHEELS; j++) {
			wheelModelmtx = glm::translate(wheelModelmtx, glm::vec3(11.0, 0.0, 0.0));
			wheels[j].display(wheelModelmtx, projmtx);
		}
	}

	// lives
	glm::mat4 lifeModelmtx = modelmtx;
	lifeModelmtx = glm::translate(lifeModelmtx, glm::vec3(5.0, 10.0, 0.0));
	for (int i = 0; i < duck->getLife(); i++) {
		lifeModelmtx = glm::translate(lifeModelmtx, glm::vec3(-6.0, 0.0, 0.0));

		color4 = getColor(color::GREEN);
		lifemodel.display(color4, lifeModelmtx, projmtx);
	}
}

void Body::rotateWheel() {
	bool isForward = duck->getForward();
	for (int i = 0; i < NUM_WHEELS; i++) {
		wheels[i].increaseAngle(
			isForward ? -(M_PI / 6) : (M_PI / 6)
		);
	}
}

Model Wheel::model = Model("resources/wheel.obj", texture_t::DUCK);

void Wheel::display(glm::mat4 modelmtx, glm::mat4 projmtx) {
	glm::mat4 wheelModelmtx = modelmtx;
	wheelModelmtx = glm::rotate(wheelModelmtx, angle, glm::vec3(0.0, 0.0, 1.0));
	glm::vec4 color4 = getColor(color::YELLOW);

	model.display(color4, wheelModelmtx, projmtx);
}