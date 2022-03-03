#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "Tank.h"

#define SCREEN_WIDTH 450
#define SCREEN_HEIGHT 300

Tank tank;

void background_display();
void update(int value);

void reshape(int w, int h) {
	float posx = (w - SCREEN_WIDTH) / 2;
	float posy = (h - SCREEN_HEIGHT) / 2;
	glViewport(posx, posy, SCREEN_WIDTH, SCREEN_HEIGHT);
	glLoadIdentity();
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
}
void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	background_display();
	tank.display();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case ' ':
		tank.fire();
		break;
	}
	glutPostRedisplay();
}

void specialkeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		tank.goRight(1.0);
		break;
	case GLUT_KEY_LEFT:
		tank.goLeft(1.0);
		break;
	}
	glutPostRedisplay();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(250, 50);
	glutInitWindowSize(800, 500);
	glutCreateWindow("BlueDuck Fortress");
	glutReshapeFunc(reshape);
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeyboard);
	glutTimerFunc(40, update, 1);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glewInit();
	glutMainLoop();
}

void background_display() {
	// Background
	glColor3f(0.8f, 0.95f, 1.0f);
	glRectf(0.0, 0.0, 100.0, 100.0);

	// Pond
	glColor3f(0.5f, 0.80f, 1.0f);
	glRectf(0.0, 0.0, 100.0, 25.0);
}

void update(int value) {
	glutPostRedisplay();
	tank.updateShell(value);
	glutTimerFunc(40, update, 1);
}