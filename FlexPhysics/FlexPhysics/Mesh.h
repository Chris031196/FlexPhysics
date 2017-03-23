#pragma once

#include "glew.h"
#include "MessageException.h"
#include "Logger.h"
#include "Loader.h"
#include <vector>
#include "glm\glm.hpp"

class Mesh
{
public:
	/*
	*	throw MessageException if obj_path is nullptr
	*
	*/
	Mesh(char* obj_path, char* bmp_path);
	~Mesh();

private:
	GLuint m_vertex_bufferID;
	GLuint m_textureID;
	int vertex_number;

	bool initTexture(char* path);
	bool initMesh(char* path);
};

