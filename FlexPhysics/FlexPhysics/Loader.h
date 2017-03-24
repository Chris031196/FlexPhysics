#pragma once

#include "glew.h"
#include <glm\glm.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include "assimp\Importer.hpp"		// C++ importer interface
#include "assimp\scene.h"			// Output data structure
#include "assimp\postprocess.h"		// Post processing flags
#include "Logger.h"

namespace loader {
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
	unsigned char* LoadBMP(const char* imagepath, int *height, int *width);
	bool loadOBJ(
		const char * path,
		std::vector<unsigned int> & indices,
		std::vector<glm::vec4> & vertices,
		std::vector<glm::vec2> & uvs,
		std::vector<glm::vec3> & normals
	);

	GLuint loadDDS(const char * imagepath);
}