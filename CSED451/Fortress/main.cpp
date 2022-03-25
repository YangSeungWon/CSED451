#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "Duck.h"
#include "Shell.h"
#include "constants.h"
#include "utils.h"

#define SCREEN_HEIGHT 300
#define SCREEN_WIDTH (SCREEN_HEIGHT * RATIO)
#define GROUND_HEIGHT 15.0

float Duck::crash_radius = 10.0;
Duck blueDuck(color::BLACK, color::BLUE, 20.0, ori_t::RIGHT);
Duck whiteDuck(color::BEIGE, color::PINK, 80.0, ori_t::LEFT);
std::vector<Shell*> shells;
bool isOver = false;
Duck* deadDuck = nullptr;

void backgroundDisplay();
void drawLives();
void drawHeart(bool fill);
void drawFullHeart();
void drawEmptyHeart();
void printGameOver();
void update(int value);
void updateShell(int value);
bool checkCrash(Duck* duck);
bool checkCrash(Shell* shell);

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
	glScalef(1.0, RATIO, 1.0);
	backgroundDisplay();
	drawLives();
	if (deadDuck != nullptr) {
		printGameOver();
	}

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
		if (checkCrash(&blueDuck)) {
			blueDuck.backLeft(1.0);
		}
		break;
	case GLUT_KEY_LEFT:
		blueDuck.goLeft(1.0);
		if (checkCrash(&blueDuck)) {
			blueDuck.backRight(1.0);
		}
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
	setColor(color::LIGHTSKYBLUE);
	glRectf(0.0, 0.0, 100.0, 100.0);

	// Pond
	setColor(color::SKYBLUE);
	glRectf(0.0, 0.0, 100.0, GROUND_HEIGHT);
}

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
	glLineWidth(1.0);

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
	glLineWidth(3.0);

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

void update(int value) {
	glutPostRedisplay();
	updateShell(value);
	if (deadDuck != nullptr) {
		deadDuck->goDown(0.2);
		if (deadDuck->getY() < -10) {
			exit(0);
		}
	}
	glutTimerFunc(50, update, 1);
}

void updateShell(int value) {
	for (auto shell = shells.begin(); shell != shells.end(); ) {
		(*shell)->update();
		if (checkCrash(*shell)) {
			shell = shells.erase(remove(shells.begin(), shells.end(), *shell));
		}
		else {
			shell++;
		}
	}
}

bool checkCrash(Duck* duck) {
	Duck* enemy = (duck == &blueDuck) ? &whiteDuck : &blueDuck;

	float x = duck->getX();
	float y = duck->getY();
	float x_enemy = enemy->getX();
	float y_enemy = enemy->getY();

	float distance = sqrt(pow(x - x_enemy, 2) + pow(y - y_enemy, 2));

	if (distance < 2 * Duck::crash_radius) {
		return true;
	}
	else {
		return false;
	}
}

bool checkCrash(Shell* shell) {
	float x = shell->getX();
	float y = shell->getY();

	// Ground
	if (y < GROUND_HEIGHT) {
		return true;
	}

	float distance;
	// blueDuck
	distance = sqrt(pow(x - blueDuck.getX(), 2) + pow(y - blueDuck.getY(), 2));
	if (distance < Duck::crash_radius) {
		if (blueDuck.strike()) {
			deadDuck = &blueDuck;
		}
		return true;
	}

	// whiteDuck
	distance = sqrt(pow(x - whiteDuck.getX(), 2) + pow(y - whiteDuck.getY(), 2));
	if (distance < Duck::crash_radius) {
		if (whiteDuck.strike()) {
			deadDuck = &whiteDuck;
		}
		return true;
	}
	
	return false;
}