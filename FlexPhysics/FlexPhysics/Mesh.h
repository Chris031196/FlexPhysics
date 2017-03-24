#pragma once

#include "glew.h"
#include "MessageException.h"
#include "Logger.h"
#include "Loader.h"
#include <vector>
#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp"

class Mesh
{
public:
	/*
	*	throws MessageException if obj_path is nullptr or fails to load .obj file
	*
	*/
	Mesh(char* obj_path, char* bmp_path);
	~Mesh();

	void draw();

	void setModelMatrix(glm::mat4 model_matrix) { m_model_matrix = model_matrix; };

	/*
	*	must be set before first use!
	*/
	static void setViewMatrix(glm::mat4 view_matrix);

	/*
	*	must be set before first use!
	*/
	static void setProjectionMatrix(glm::mat4 projection_matrix);

private:
	//mesh buffers
	GLuint m_index_buffer_ID;
	GLuint m_vertex_buffer_ID;
	GLuint m_texture_ID;
	//number of vertices
	int m_vertex_number;
	//model matrix
	glm::mat4 m_model_matrix;

	bool initTexture(char* path);
	bool initMesh(char* path);
	bool initShaders();

	//shaderprogram data
	static GLuint program_ID;
	static GLuint uniform_loc_modelmatrix;
	static GLuint uniform_loc_viewmatrix;
	static GLuint uniform_loc_projectionmatrix;
	static GLuint uniform_loc_texsampler;
};

