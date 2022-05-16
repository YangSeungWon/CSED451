#pragma once
#include <iostream>
#include <glm/vec4.hpp>
#include "utils.h"

class Sun {
private:
	float theta = 5;
	float deltaTheta = 2;
public:
	void move() {
		theta += deltaTheta;
		if (theta >= 180) {
			theta = 180;
			deltaTheta = -deltaTheta;
		}
		else if (theta <= 0) {
			theta = 0;
			deltaTheta = -deltaTheta;
		}
	}
	glm::vec4 getPos() { return glm::vec4(cos(degToRad(theta)), sin(degToRad(theta)), 0.0, 0.0); }
	//glm::vec4 getPos() { return glm::vec4(0.0, 0.0, 0.0, 1.0); }
};