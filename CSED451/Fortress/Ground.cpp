#include <vector>
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Ground.h"
#include "Model.h"
#include "utils.h"

Model Ground::model = Model("");

Ground::Ground() {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	for (int i = -width / 2; i < width - (width / 2); i++) {
		for (int j = -height / 2; j < height - (height / 2); j++) {
			vertices.push_back(glm::vec3(i * interval, 0, j * interval));
			vertices.push_back(glm::vec3(i * interval, 0, (j + 1) * interval));
			vertices.push_back(glm::vec3((i + 1) * interval, 0, j * interval));
			vertices.push_back(glm::vec3(i * interval, 0, (j + 1) * interval));
			vertices.push_back(glm::vec3((i + 1) * interval, 0, (j + 1) * interval));
			vertices.push_back(glm::vec3((i + 1) * interval, 0, j * interval));
			uvs.push_back(glm::vec2(0, 0));
			uvs.push_back(glm::vec2(0, 1));
			uvs.push_back(glm::vec2(1, 0));
			uvs.push_back(glm::vec2(0, 1));
			uvs.push_back(glm::vec2(1, 1));
			uvs.push_back(glm::vec2(1, 0));
			normals.push_back(glm::vec3(0, 1, 0));
			normals.push_back(glm::vec3(0, 1, 0));
			normals.push_back(glm::vec3(0, 1, 0));
			normals.push_back(glm::vec3(0, 1, 0));
			normals.push_back(glm::vec3(0, 1, 0));
			normals.push_back(glm::vec3(0, 1, 0));
		}
	}

	model.setModel(vertices, uvs, normals);
}

void Ground::display(glm::mat4 modelmtx, glm::mat4 projmtx) {
	glm::vec4 color;
	glm::mat4 groundModelmtx;
	for (int i = 0; i < 3; i++) {
		groundModelmtx = glm::translate(modelmtx, glm::vec3(interval * width * (-1 + i), 0, -interval * height));
		for (int j = 0; j < 3; j++) {
			if (i == 1 && j == 1) {
				color = getColor(color::LIGHTSKYBLUE);
			}
			else {
				color = getColor(color::LIGHTGRAY);
			}

			model.display(color, groundModelmtx, projmtx);
			groundModelmtx = glm::translate(groundModelmtx, glm::vec3(0, 0, interval * height));
		}
	}
}