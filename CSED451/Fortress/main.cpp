#include <iostream>
#include <cstdlib>
#include <ctime>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "Duck.h"
#include "Shell.h"
#include "Ground.h"
#include "constants.h"
#include "utils.h"
#include "drawFunctions.h"

float Duck::crash_radius = 20.0;
Duck blueDuck(color::BLACK, color::BLUE, -50.0, 0.0, 0.0, 0.0);
Duck whiteDuck(color::BEIGE, color::PINK, 50.0, 0.0, 0.0, 180.0);
std::vector<Shell*> shells;
bool isOver = false;
Duck* deadDuck = nullptr;
bool allPass = false;
bool allFail = false;
Ground ground;

view_t viewing_mode = view_t::THIRD_PERSON;
bool hiddenLineRemoval = false;

void reshape(int w, int h);
void renderScene(void);
void keyboard(unsigned char key, int x, int y);
void specialkeyboard(int key, int x, int y);
void update(int value);
void updateShell(int value);
void randomFire(int value);
bool checkCrash(Duck* duck);
bool checkCrash(Shell* shell);

void main(int argc, char** argv) {
	std::srand(static_cast<unsigned int>(std::time(0)));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(250, 50);
	glutInitWindowSize(800, 500);
	glutCreateWindow("BlueDuck Fortress");
	glutReshapeFunc(reshape);
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeyboard);
	glutTimerFunc(UPDATE_INTERVAL, update, 1);
	glutTimerFunc(1000, randomFire, 0);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glewInit();
	glutMainLoop();
}

void reshape(int w, int h) {
	int viewWidth = 1000;
	int viewHeight = 1000;
	glViewport((w - viewWidth) / 2, (h - viewHeight) / 2, viewWidth, viewHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluPerspective(90, 1, 0.1, 4333.0);

	switch (viewing_mode) {
	case view_t::THIRD_PERSON:
		gluLookAt(0, 0, 150, 0, 0, 0, 0, 1, 0);
		break;
	case view_t::FIRST_PERSON:
		glm::vec3 eyePos = blueDuck.getHeadPos() + glm::vec3(0, 15, 0);
		glm::vec3 eyeLookAt = blueDuck.getBeakPos();
		glm::vec3 cameraUp = glm::vec3(0, 1, 0);
		//gluLookAt(0, 0, 150, 0, 0, 0, 0, 1, 0);
		gluLookAt(
			eyePos.x, eyePos.y, eyePos.z,
			eyeLookAt.x, eyeLookAt.y, eyeLookAt.z,
			cameraUp.x, cameraUp.y, cameraUp.z
		);
		break;
	case view_t::TOP_VIEW:
		gluLookAt(0, 400, 0, 0, 0, 0, 0, 0, -1);
		break;
	}

	glScalef(1.0, 1.0, 1.0);
	//glTranslatef(0, 0, -100);

	// Clear the screen
	glClearDepthf(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);

	ground.display();
	//drawLives();
	if (hiddenLineRemoval) {
		glEnable(GL_CULL_FACE);
	}
	else {
		glDisable(GL_CULL_FACE);
	}

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
		if (!allFail) {
			blueDuck.fire();
		}
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
	case 'a':
		blueDuck.rotateHead(15.0);
		break;
	case 'd':
		blueDuck.rotateHead(-15.0);
		break;
	case 'c':
		allPass = !allPass;
		break;
	case 'f':
		allFail = !allFail;
		break;
	case 'v':
		if (viewing_mode == view_t::THIRD_PERSON) {
			viewing_mode = view_t::FIRST_PERSON;
		}
		else if (viewing_mode == view_t::FIRST_PERSON) {
			viewing_mode = view_t::TOP_VIEW;
		}
		else if (viewing_mode == view_t::TOP_VIEW) {
			viewing_mode = view_t::THIRD_PERSON;
		}
		break;
	case 'r':
		hiddenLineRemoval = !hiddenLineRemoval;
		break;
	}
	glutPostRedisplay();
}

void specialkeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		blueDuck.goForward(1.0);
		if (checkCrash(&blueDuck)) {
			blueDuck.goBack(1.0);
		}
		break;
	case GLUT_KEY_DOWN:
		blueDuck.goBack(1.0);
		if (checkCrash(&blueDuck)) {
			blueDuck.goForward(1.0);
		}
		break;
	case GLUT_KEY_LEFT:
		blueDuck.rotate(15.0);
		break;
	case GLUT_KEY_RIGHT:
		blueDuck.rotate(-15.0);
		break;
	}
	glutPostRedisplay();
}

void update(int value) {
	glutPostRedisplay();
	updateShell(value);

	blueDuck.recoil();
	whiteDuck.recoil();

	// Gameover Animation
	if (deadDuck != nullptr) {
		deadDuck->goDown(0.2);
		if (deadDuck->getPos().y < -10) {
			exit(0);
		}
	}
	glutTimerFunc(UPDATE_INTERVAL, update, 1);
}

void updateShell(int value) {
	for (auto shell = shells.begin(); shell != shells.end();) {
		(*shell)->update();
		if (checkCrash(*shell)) {
			shell = shells.erase(remove(shells.begin(), shells.end(), *shell));
		}
		else {
			shell++;
		}
	}
}

void randomFire(int value) {
	if (deadDuck == &whiteDuck) {
		return;
	}

	if (allPass) {
		glutTimerFunc(300, randomFire, (value + 1) % 8);
		return;
	}

	if (value == 7) {
		whiteDuck.fire();
		glutTimerFunc(1000, randomFire, 0);
		return;
	}

	int randomNumber = std::rand() % 4;
	switch (randomNumber) {
	case 0:
		whiteDuck.increaseBeakAngle();
		break;
	case 1:
		whiteDuck.decreaseBeakAngle();
		break;
	case 2:
		whiteDuck.increaseBeakPower();
		break;
	case 3:
		whiteDuck.decreaseBeakPower();
		break;
	}

	glutTimerFunc(300, randomFire, value + 1);
}

bool checkCrash(Duck* duck) {
	Duck* enemy = (duck == &blueDuck) ? &whiteDuck : &blueDuck;

	float distance = glm::length(duck->getPos() - enemy->getPos());

	if (distance < 2 * Duck::crash_radius) {
		return true;
	}
	else {
		return false;
	}
}

bool checkCrash(Shell* shell) {
	float distance;
	glm::vec3 shellPos = shell->getPos();

	// Ground
	if (shellPos.y < 0) {
		return true;
	}

	// blueDuck
	distance = glm::length(blueDuck.getPos() - shellPos);
	if (distance < Duck::crash_radius) {
		if (blueDuck.strike(allFail ? 3 : 1)) {
			if (deadDuck == nullptr) {
				deadDuck = &blueDuck;
			}
		}
		return true;
	}

	// whiteDuck
	distance = glm::length(whiteDuck.getPos() - shellPos);
	if (distance < Duck::crash_radius) {
		if (whiteDuck.strike(allPass ? 3 : 1)) {
			if (deadDuck == nullptr) {
				deadDuck = &whiteDuck;
			}
		}
		return true;
	}
	
	return false;
}