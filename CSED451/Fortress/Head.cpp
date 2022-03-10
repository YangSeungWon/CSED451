#include "Head.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include <windows.h>
#include <algorithm>
#include "Shell.h"
#include "Duck.h"
#include "constant.h"

float Head::getX() { return duck->getX() + offsetX; }
float Head::getY() { return duck->getY() + offsetY; }

void Head::display() {
	float x = duck->getX() + offsetX;
	float y = duck->getY() + offsetY;
	float angle;

	// crown
	glColor3f(0.0f, 0.6f, 0.9f);
	glBegin(GL_POLYGON);
		for (angle = 0; angle < 2 * M_PI; angle += M_PI / 180) {
			glVertex2f(x + 0.0, y + 7.0);
			glVertex2f(x + 2.0, y + 10.0);
			glVertex2f(x + 3.0, y + 7.0);
			glVertex2f(x + 5.0, y + 8.0);
			glVertex2f(x + 5.0, y + 5.0);
			glVertex2f(x + 7.0, y + 3.0);
			glVertex2f(x + 5.0, y + 0.0);
		}
	glEnd();

	// head
	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_POLYGON);
		for (angle = 0; angle < 2 * M_PI; angle += M_PI / 180) {
			glVertex2f(x + radius * cos(angle), y + RATIO * radius * sin(angle));
		}
	glEnd();

	// eye
	glColor3f(1.0f, 1.0f, 1.0f);
	float e_radius = 0.3 * radius;
	glBegin(GL_POLYGON);
		for (angle = 0; angle < 2 * M_PI; angle += M_PI / 180) {
			glVertex2f(x - 1.0 + e_radius * cos(angle), y + 2.0 + RATIO * e_radius * sin(angle));
		}
	glEnd();

	// pupil
	glColor3f(0.0f, 0.6f, 0.9f);
	float p_radius = 0.2 * radius;
	glBegin(GL_POLYGON);
		for (angle = 0; angle < 2 * M_PI; angle += M_PI / 180) {
			glVertex2f(x - 1.3 + p_radius * cos(angle), y + 2.7 + RATIO * p_radius * sin(angle));
		}
	glEnd();

	// beak
	beak.display();
}

void Head::fire() {
	beak.fire();
}

void Head::updateShell(int value) {
	beak.updateShell(value);
}

void Beak::display() {
	glColor3f(0.9f, 0.75f, 0.3f);

	float x = head->getX();
	float y = head->getY();
	float radius = head->getRadius();

	glBegin(GL_POLYGON);
		glVertex2f(x - 0.6 * radius, y + 1.2 * radius);
		glVertex2f(x - 1.0 * radius, y - 0 * radius);
		glVertex2f(x - 1.5 * radius, y + 1.3 * radius);
	glEnd();

	for (Shell* _shell : shell) {
		_shell->display();
	}
}

void Beak::fire() {
	float x = head->getX();
	float y = head->getY();
	Shell* new_shell = new Shell(x - 6.5, y + 5.5);
	shell.push_back(new_shell);
}

void Beak::updateShell(int value) {
	for (auto i = shell.begin(); i != shell.end(); ) {
		if (!(*i)->update()) {
			i = shell.erase(remove(shell.begin(), shell.end(), *i));
		}
		else {
			i++;
		}
	}
}