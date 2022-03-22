#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "Duck.h"
#include "Shell.h"
#include "constants.h"

#define SCREEN_HEIGHT 300
#define SCREEN_WIDTH (SCREEN_HEIGHT * RATIO)

Duck blueDuck(20.0, ori_t::RIGHT);
Duck whiteDuck(80.0, ori_t::LEFT);
std::vector<Shell*> shells;

void backgroundDisplay();
void update(int value);
void updateShell(int value);

void reshape(int w, int h) {
	float posx = (w - SCREEN_WIDTH) / 2;
	float posy = (h - SCREEN_HEIGHT) / 2;
	glViewport(posx, posy, SCREEN_WIDTH, SCREEN_HEIGHT);
	glLoadIdentity();
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
	backgroundDisplay();
	glScalef(1.0, RATIO, 1.0);

	for (Shell* _shell : shells) {
		glPushMatrix();
		_shell->display();
		glPopMatrix();
	}

	glPushMatrix();
	blueDuck.display();
	glPopMatrix();

	glPushMatrix();
	whiteDuck.display();
	glPopMatrix();

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case ' ':
		blueDuck.fire();
		break;
	case 'w':
		blueDuck.increaseBeakAngle();
		break;
	case 's':
		blueDuck.decreaseBeakAngle();
		break;
	case 'e':
		blueDuck.increaseBeakPower();
		break;
	case 'q':
		blueDuck.decreaseBeakPower();
		break;
	}
	glutPostRedisplay();
}

void specialkeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		blueDuck.goRight(1.0);
		break;
	case GLUT_KEY_LEFT:
		blueDuck.goLeft(1.0);
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
	glutTimerFunc(50, update, 1);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glewInit();
	glutMainLoop();
}

void backgroundDisplay() {
	// Background
	glColor3f(0.8f, 0.95f, 1.0f);
	glRectf(0.0, 0.0, 100.0, 100.0);

	// Pond
	glColor3f(0.5f, 0.80f, 1.0f);
	glRectf(0.0, 0.0, 100.0, 25.0);
}

void update(int value) {
	glutPostRedisplay();
	updateShell(value);
	glutTimerFunc(50, update, 1);
}

void updateShell(int value) {
	std::cout << "update\n";
	for (auto shell = shells.begin(); shell != shells.end(); ) {
		std::cout << (*shell)->dy << '\n';
		if (!(*shell)->update()) {
			shell = shells.erase(remove(shells.begin(), shells.end(), *shell));
		}
		else {
			shell++;
		}
	}
}