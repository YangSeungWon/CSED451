#include "Shell.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "constants.h"
#include "utils.h"
#include "Model.h"

extern bool hiddenLineRemoval;

Model Shell::model = Model("resources/shell.obj");

Shell::Shell(glm::vec3 _pos, glm::vec3 _velocity) {
	pos = _pos;
	velocity = _velocity;
}

void Shell::display(glm::mat4 modelmtx, glm::mat4 projmtx) {
	float angle;
	glm::vec4 color4;
	glm::mat4 shellModelmtx = modelmtx;
	color4 = getColor(color::GREEN);
	shellModelmtx = glm::translate(shellModelmtx, glm::vec3(pos.x, pos.y, pos.z));
	model.display(color4, shellModelmtx, projmtx);
}

void Shell::update() {
	pos += velocity;
	velocity.y -= 0.5;
}