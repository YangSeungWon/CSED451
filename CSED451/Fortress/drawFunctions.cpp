#include "drawFunctions.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include "Duck.h"
#include "constants.h"
#include "utils.h"

extern Duck blueDuck;
extern Duck whiteDuck;

void drawLives() {
	int i;
	glPushMatrix();

	// BlueDuck
	glTranslatef(0.0f, 60.0f, 0.0f);
	setColor(color::BLUE);
	int blueDuckLife = blueDuck.getLife();
	for (i = 0; i < blueDuckLife; i++) {
		glTranslatef(7.0f, 0.0f, 0.0f);
		drawFullHeart();
	}
	for (; i < 3; i++) {
		glTranslatef(7.0f, 0.0f, 0.0f);
		drawEmptyHeart();
	}

	// WhiteDuck
	glTranslatef(50.0f, 0.0f, 0.0f);
	setColor(color::PINK);
	int whiteDuckLife = whiteDuck.getLife();

	for (i = 0; i < whiteDuckLife; i++) {
		glTranslatef(7.0f, 0.0f, 0.0f);
		drawFullHeart();
	}
	for (; i < 3; i++) {
		glTranslatef(7.0f, 0.0f, 0.0f);
		drawEmptyHeart();
	}

	glPopMatrix();
}

void drawHeart(bool fill) {
	glBegin(fill ? GL_POLYGON : GL_LINE_LOOP);
	glVertex2f(0.0, 0.0);
	glVertex2f(1.0, 1.0);
	glVertex2f(2.0, 1.0);
	glVertex2f(3.0, 0.0);
	glVertex2f(3.0, -1.0);
	glVertex2f(0.0, -4.0);
	glVertex2f(-3.0, -1.0);
	glVertex2f(-3.0, 0.0);
	glVertex2f(-2.0, 1.0);
	glVertex2f(-1.0, 1.0);
	glEnd();
}

void drawFullHeart() {
	drawHeart(true);
}

void drawEmptyHeart() {
	drawHeart(false);
}

void printGameOver() {
	setColor(color::BLACK);
	glPushMatrix();

	glTranslatef(18.0f, 50.0f, 0.0f);
	glScalef(3.0, 3.0, 0.0);

	// G
	glBegin(GL_LINE_STRIP);
	glVertex2f(2.0, 0.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, -2.0);
	glVertex2f(2.0, -2.0);
	glVertex2f(2.0, -1.0);
	glVertex2f(1.0, -1.0);
	glEnd();

	// A
	glTranslatef(2.5, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.0, -2.0);
	glVertex2f(1.0, 0.0);
	glVertex2f(2.0, -2.0);
	glEnd();

	// M
	glTranslatef(2.5, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.0, -2.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(1.0, -1.0);
	glVertex2f(2.0, 0.0);
	glVertex2f(2.0, -2.0);
	glEnd();

	// E
	glTranslatef(2.5, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(2.0, 0.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, -1.0);
	glVertex2f(2.0, -1.0);
	glVertex2f(0.0, -1.0);
	glVertex2f(0.0, -2.0);
	glVertex2f(2.0, -2.0);
	glEnd();

	// ' '
	glTranslatef(2.5, 0.0, 0.0);

	// O
	glTranslatef(2.5, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0, 0.0);
	glVertex2f(2.0, 0.0);
	glVertex2f(2.0, -2.0);
	glVertex2f(0.0, -2.0);
	glEnd();

	// V
	glTranslatef(2.5, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.0, 0.0);
	glVertex2f(1.0, -2.0);
	glVertex2f(2.0, 0.0);
	glEnd();

	// E
	glTranslatef(2.5, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(2.0, 0.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, -1.0);
	glVertex2f(2.0, -1.0);
	glVertex2f(0.0, -1.0);
	glVertex2f(0.0, -2.0);
	glVertex2f(2.0, -2.0);
	glEnd();

	// R
	glTranslatef(2.5, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.0, -2.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(2.0, 0.0);
	glVertex2f(2.0, -1.0);
	glVertex2f(0.0, -1.0);
	glVertex2f(2.0, -2.0);
	glEnd();

	glPopMatrix();
}