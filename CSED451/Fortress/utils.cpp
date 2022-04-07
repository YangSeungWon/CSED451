#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include "constants.h"
#include "utils.h"

void drawModel(std::vector< glm::vec3 > vertices, std::vector< glm::vec2 > uvs) {
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
}

void drawCircle(float radius) {
	float angle;
	glBegin(GL_POLYGON);
	for (angle = 0; angle < 2 * M_PI; angle += M_PI / 180) {
		glVertex2f(radius * cos(angle), radius * sin(angle));
	}
	glEnd();
}

float radToDeg(float rad) {
	return rad / M_PI * 180;
}

float degToRad(float deg) {
	return deg / 180 * M_PI;
}

void setColor(color _color) {
	switch (_color) {
	case color::BLACK:
		glColor3f(0.2f, 0.2f, 0.2f);
		break;
	case color::BLUE:
		glColor3f(0.0f, 0.6f, 0.9f);
		break;
	case color::BEIGE:
		glColor3f(0.9f, 0.8f, 0.7f);
		break;
	case color::PINK:
		glColor3f(1.0f, 0.6f, 0.6f);
		break;
	case color::SKYBLUE:
		glColor3f(0.5f, 0.8f, 1.0f);
		break;
	case color::LIGHTSKYBLUE:
		glColor3f(0.8f, 0.95f, 1.0f);
		break;
	case color::WHITE:
		glColor3f(1.0f, 1.0f, 1.0f);
		break;
	case color::YELLOW:
		glColor3f(0.9f, 0.65f, 0.3f);
		break;
	}
}