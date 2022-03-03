#include "Tank.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include <windows.h>
#include <algorithm>
#include "Shell.h"

void Tank::display() {
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(x - 10.0, y, x + 10.0, y + 20.0);

	for (Shell* _shell : shell) {
		_shell->display();
	}
}

void Tank::goRight(float d) { 
	x += d; 
	if (x < 0) {
		x = 0;
	}
	else if (x > 100) {
		x = 100;
	}
}

void Tank::goLeft(float d) {
	x -= d; 
	if (x < 0) {
		x = 0;
	}
	else if (x > 100) {
		x = 100;
	}
}

void Tank::fire() {
	Shell* new_shell = new Shell(x, y);
	shell.push_back(new_shell);
}

void Tank::updateShell(int value) {
	for (auto i = shell.begin(); i != shell.end(); ) {
		if (!(*i)->update()) {
			i = shell.erase(remove(shell.begin(), shell.end(), *i));
		}
		else {
			i++;
		}
	}
}