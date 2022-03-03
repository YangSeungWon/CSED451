#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
std::vector<glm::vec3> position = {
glm::vec3(0.0f, 0.0f, 0.0f),
glm::vec3(1.0f, 0.0f, 0.0f),
glm::vec3(0.0f, 1.0f, 0.0f),
};
void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	for (size_t i = 0; i < position.size(); i++) {
		glVertex3f(position[i][0], position[i][1], position[i][2]);
	}
	glEnd();
	glFlush();
}
void main(int argc, char** argv) {
	// inspect array elements and print to console
	const float* probe = &position[0].x;
	for (size_t i = 0; i < position.size() * 3; i++) {
		std::cout << probe[i] << std::endl;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Hello OpenGL");
	glutDisplayFunc(renderScene);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glewInit();
	glutMainLoop();
}
