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
	glTranslatef(x, y, z);
	glRotatef(angle, 0, 1, 0);
	if (isRecoil) {
		glTranslatef(displacement, 0.0, 0.0);
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

void Duck::goForward(float d) {
	isForward = true;
	x += d * cos(degToRad(angle));
	z += -d * sin(degToRad(angle));

	if (x < -GROUND_BOUNDARY) {
		x = -GROUND_BOUNDARY;
	}
	else if (x > GROUND_BOUNDARY) {
		x = GROUND_BOUNDARY;
	}

	if (z < -GROUND_BOUNDARY) {
		z = -GROUND_BOUNDARY;
	}
	else if (z > GROUND_BOUNDARY) {
		z = GROUND_BOUNDARY;
	}
	body.rotateWheel();
}

void Duck::goBack(float d) {
	isForward = false;
	x -= d * cos(degToRad(angle));
	z -= -d * sin(degToRad(angle));

	if (x < -GROUND_BOUNDARY) {
		x = -GROUND_BOUNDARY;
	}
	else if (x > GROUND_BOUNDARY) {
		x = GROUND_BOUNDARY;
	}

	if (z < -GROUND_BOUNDARY) {
		z = -GROUND_BOUNDARY;
	}
	else if (z > GROUND_BOUNDARY) {
		z = GROUND_BOUNDARY;
	}
	body.rotateWheel();
}

void Duck::goDown(float d) {
	y -= d;
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