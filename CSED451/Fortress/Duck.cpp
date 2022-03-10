#include "Duck.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include <windows.h>
#include <algorithm>
#include "Shell.h"

Duck::Duck() : head{ Head(this) }, body{ Body(this) } {

}

void Duck::display() {
	head.display();
	body.display();
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

void Duck::updateShell(int value) {
	head.updateShell(value);
}