#include "Duck.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <ctime>
#include "Shell.h"
#include "constants.h"
#include "utils.h"


void Duck::display() {
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(angle, 0, 1, 0);
	if (isRecoil) {
		glRotatef(headAngle, 0, 1, 0);
		glTranslatef(displacement, 0.0, 0.0);
		glRotatef(-headAngle, 0, 1, 0);
	}
	glPushMatrix();
	glTranslatef(13.0, 22.0, 0.0);
	glRotatef(headAngle, 0, 1, 0);
	head.display();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 10.0, 0.0);
	body.display();
	glPopMatrix();
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

bool Duck::strike(int power) {
	life -= power;
	if (life <= 0) {
		return true;
	}
	else {
		return false;
	}
}