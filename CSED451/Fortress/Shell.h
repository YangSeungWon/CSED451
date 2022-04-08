#pragma once
#include <glm/vec3.hpp>
class Shell
{
private:
	glm::vec3 pos;
	glm::vec3 velocity;
public:
	Shell(glm::vec3 _pos, glm::vec3 _velocity);
	glm::vec3 getPos() { return pos; }
	void display();
	void update();
};

