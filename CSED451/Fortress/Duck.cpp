#include "Duck.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include <windows.h>
#include <algorithm>
#include "Shell.h"
#include "constants.h"


void Duck::display() {
	glTranslatef(x, y, 0.0);
	if (orientation == ori_t::LEFT) {
		glScalef(-1.0f, 1.0f, 1.0f);
	}
	glPushMatrix();
	glTranslatef(5.0, 14.0, 0.0);
	head.display();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 6.5, 0.0);
	body.display();
	glPopMatrix();
}

void Duck::goRight(float d) { 
	orientation = ori_t::RIGHT;
	x += d; 
	if (x < 0) {
		x = 0;
	}
	else if (x > 100) {
		x = 100;
	}
	body.rotateWheel();
}

void Duck::goLeft(float d) {
	orientation = ori_t::LEFT;
	x -= d; 
	if (x < 0) {
		x = 0;
	}
	else if (x > 100) {
		x = 100;
	}
	body.rotateWheel();
}

void Duck::backRight(float d) {
	x += d;
}

void Duck::backLeft(float d) {
	x -= d;
}

void Duck::goDown(float d) {
	y -= d;
}

void Duck::fire() {
	head.fire();
}

bool Duck::strike() {
	life--;
	if (life <= 0) {
		return true;
	}
	else {
		return false;
	}
}