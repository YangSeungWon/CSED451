#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

#include "utils.h"
#include "Model.h"

extern bool hiddenLineRemoval;

// Very, VERY simple OBJ loader.
// Here is a short list of features a real function would provide : 
// - Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
// - Animations & bones (includes bones weights)
// - Multiple UVs
// - All attributes should be optional, not "forced"
// - More stable. Change a line in the OBJ file and it crashes.
// - More secure. Change another line and you can inject code.
// - Loading from memory, stream, etc

bool Model::loadOBJ() {
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE* file;
	if (fopen_s(&file, path, "r") != 0) {
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, 128);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		vertices.push_back(vertex);
		uvs.push_back(uv);
		normals.push_back(normal);

	}
	fclose(file);
	return true;
}

bool Model::load() {
	if (!isLoaded) {
		isLoaded = loadOBJ();
	}
	return isLoaded;
}

void Model::display() {
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

	if (hiddenLineRemoval) {
		setColor(color::DARKGRAY);
		glPushMatrix();
		glScalef(0.99, 0.99, 0.99);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		glPopMatrix();
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
}

void Model::setModel(std::vector<glm::vec3> _vertices,
	std::vector<glm::vec2> _uvs,
	std::vector<glm::vec3> _normals) {
	vertices = _vertices;
	uvs = _uvs;
	normals = _normals;
}