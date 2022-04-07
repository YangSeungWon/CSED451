#include <vector>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "Ground.h"
#include "Model.h"

Model Ground::model = Model("");

Ground::Ground() {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	for (int i = -width / 2; i < width - (width / 2) - 1; i++) {
		for (int j = -height / 2; j < height - (height / 2) - 1; j++) {
			vertices.push_back(glm::vec3(i * interval, 0, j * interval));
			vertices.push_back(glm::vec3((i + 1) * interval, 0, j * interval));
			vertices.push_back(glm::vec3(i * interval, 0, (j + 1) * interval));
			vertices.push_back(glm::vec3(i * interval, 0, (j + 1) * interval));
			vertices.push_back(glm::vec3((i + 1) * interval, 0, j * interval));
			vertices.push_back(glm::vec3((i + 1) * interval, 0, (j + 1) * interval));
			uvs.push_back(glm::vec2(0, 0));
			uvs.push_back(glm::vec2(0, 0));
			uvs.push_back(glm::vec2(0, 0));
			normals.push_back(glm::vec3(0, 0, 1));
			normals.push_back(glm::vec3(0, 0, 1));
			normals.push_back(glm::vec3(0, 0, 1));
		}
	}

	model.setModel(vertices, uvs, normals);
}

void Ground::display() {
	model.display();
}