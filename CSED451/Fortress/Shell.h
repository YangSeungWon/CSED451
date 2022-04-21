#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Model.h"

class Shell
{
private:
	glm::vec3 pos;
	glm::vec3 velocity;
public:
	Shell(glm::vec3 _pos, glm::vec3 _velocity);
	static Model model;
	glm::vec3 getPos() { return pos; }
	void display(glm::mat4 modelmtx, glm::mat4 projmtx);
	void update();
};

