#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

class Model {
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	const char* path;
	bool isLoaded = false;
	bool loadOBJ();
public:
	Model(const char* _path) : path(_path) { }
	bool load();
	void display();
	void setModel(std::vector<glm::vec3> _vertices,
		std::vector<glm::vec2> _uvs,
		std::vector<glm::vec3> _normals);
};
