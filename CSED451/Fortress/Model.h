#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <GL/glew.h>
#include "constants.h"

class Model {
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	const char* path;
	bool isLoaded = false;
	bool loadOBJ();
	texture_t textureIdx;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
public:
	Model(const char* _path, texture_t _textureIdx) : path(_path), textureIdx(_textureIdx) { }
	bool load();
	void display(glm::vec4 color, glm::mat4 modelmtx, glm::mat4 projmtx);
	void setModel(std::vector<glm::vec3> _vertices,
		std::vector<glm::vec2> _uvs,
		std::vector<glm::vec3> _normals);
};
