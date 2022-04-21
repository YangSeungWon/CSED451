#include "Duck.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <ctime>
#include "Shell.h"
#include "constants.h"
#include "utils.h"

extern unsigned int ID;

void Duck::display(glm::mat4 modelmtx, glm::mat4 projmtx) {
	glm::mat4 duckModelmtx = modelmtx;
	duckModelmtx = glm::translate(duckModelmtx, glm::vec3(pos.x, pos.y, pos.z));
	duckModelmtx = glm::rotate(duckModelmtx, degToRad(angle), glm::vec3(0, 1, 0));
	if (isRecoil) {
		duckModelmtx = glm::rotate(duckModelmtx, degToRad(headAngle), glm::vec3(0, 1, 0));
		duckModelmtx = glm::translate(duckModelmtx, glm::vec3(displacement, 0.0, 0.0));
		duckModelmtx = glm::rotate(duckModelmtx, degToRad (-headAngle), glm::vec3(0, 1, 0));
	}

	glm::mat4 headModelmtx = duckModelmtx;
	headModelmtx = glm::translate(headModelmtx, glm::vec3(13.0, 22.0, 0.0));
	headModelmtx = glm::rotate(headModelmtx, degToRad(headAngle), glm::vec3(0, 1, 0));
	head.display(headModelmtx, projmtx);

	glm::mat4 bodyModelmtx = duckModelmtx;
	bodyModelmtx = glm::translate(bodyModelmtx, glm::vec3(0.0, 10.0, 0.0));
	body.display(bodyModelmtx, projmtx);
}

void Duck::cageInBoundary() { 
	if (pos.x < -GROUND_BOUNDARY) {
		pos.x = -GROUND_BOUNDARY;
	}
	else if (pos.x > GROUND_BOUNDARY) {
		pos.x = GROUND_BOUNDARY;
	}

	if (pos.z < -GROUND_BOUNDARY) {
		pos.z = -GROUND_BOUNDARY;
	}
	else if (pos.z > GROUND_BOUNDARY) {
		pos.z = GROUND_BOUNDARY;
	}
}

void Duck::goForward(float d) {
	isForward = true;
	pos += glm::vec3(d * cos(degToRad(angle)), 0, -d * sin(degToRad(angle)));

	cageInBoundary();
	body.rotateWheel();
}

void Duck::goBack(float d) {
	isForward = false;
	pos.x -= d * cos(degToRad(angle));
	pos.z -= -d * sin(degToRad(angle));

	cageInBoundary();
	body.rotateWheel();
}

void Duck::goDown(float d) {
	pos.y -= d;
}

void Duck::fire() {
	if (!isRecoil) {
		lastFirePower = head.fire();
		lastFireTime = (float)std::clock();

		// setup recoil
		isRecoil = true;
		displacement = 0.0f;
		velocity = -2.0f * lastFirePower;
	}
}

void Duck::recoil() {
	displacement += velocity;
	velocity -= displacement * SPRING_FORCE * UPDATE_INTERVAL / 1000.0f;
	velocity *= 1.0 - DAMPING * UPDATE_INTERVAL / 1000.0f;

	if (abs(displacement) < 0.2f && abs(velocity) < 0.2f) {
		isRecoil = false;
	}
}

void Duck::rotateHead(float _angle) { 
	headAngle += _angle; 
	if (headAngle < -90) {
		headAngle = -90;
	}
	else if (headAngle > 90) {
		headAngle = 90;
	}
}

glm::vec3 Duck::getHeadPos() {
	glm::vec3 headPos = pos + (
			(float)displacement * glm::vec3(
				cos(degToRad(angle + headAngle)), 
				0, 
				-sin(degToRad(angle + headAngle))
			)
		);

	// head
	headPos += glm::vec3(
		13.0 * cos(degToRad(angle)),
		22.0,
		-13.0 * sin(degToRad(angle))
	);

	return headPos;
}

bool Duck::strike(int power) {
	life -= power;
	if (life <= 0) {
		return true;
	}
	else {
		return false;
	}
}