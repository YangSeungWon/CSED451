#include "Duck.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include <windows.h>
#include <algorithm>
#include "Shell.h"


void Duck::display() {
	glTranslatef(x, y, 0.0);
	glPushMatrix();
	glTranslatef(-5.0, 14.0, 0.0);
	head.display();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 6.5, 0.0);
	body.display();
	glPopMatrix();
}

void Duck::goRight(float d) { 
	x += d; 
	if (x < 0) {
		x = 0;
	}
	else if (x > 100) {
		x = 100;
	}
}

void Duck::goLeft(float d) {
	x -= d; 
	if (x < 0) {
		x = 0;
	}
	else if (x > 100) {
		x = 100;
	}
}

void Duck::fire() {
	head.fire();
}
