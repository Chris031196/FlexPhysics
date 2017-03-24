#include "Mesh.h"

GLuint Mesh::program_ID = 0;
GLuint Mesh::uniform_loc_modelmatrix = 0;
GLuint Mesh::uniform_loc_viewmatrix = 0;
GLuint Mesh::uniform_loc_projectionmatrix = 0;
GLuint Mesh::uniform_loc_texsampler = 0;

Mesh::Mesh(char * obj_path, char * bmp_path)
{
	//initialize mesh
	bool success = false;
	if (obj_path != nullptr)
		success = initMesh(obj_path);
	else
		throw MessageException("Path to .obj file is empty!");
		
	if(!success)
		throw MessageException("Error while loading .obj file!");

	//initialize texture
	if (bmp_path != nullptr)
		success = initTexture(bmp_path);
	else
		m_texture_ID = 0;
	
	//if texture loading fails, program continues without texture
	if (!success) {
		logger::error("Texturefile %s couldn't be loaded!", bmp_path);
		m_texture_ID = 0;
	}

	//initialize shader program if it isn't already
	if (program_ID == 0) {
		initShaders();
	}
	
	m_model_matrix = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_vertex_buffer_ID);
	glDeleteBuffers(1, &m_index_buffer_ID);
	glDeleteTextures(1, &m_texture_ID);
}


bool Mesh::initTexture(char * path)
{
	int height, width;
	//load image from .bmp file
	unsigned char* image_data = loader::LoadBMP(path, &height, &width);
	if (height == 0 || width == 0) {
		logger::error("Failed to load .bmp file \"%s\"!", path);
		return false;
	}

	//generate texture and fill it with data
	glGenTextures(1, &m_texture_ID);
	glBindTexture(GL_TEXTURE_2D, m_texture_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, image_data);

	//setup opengl texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	return true;
}

bool Mesh::initMesh(char * path)
{
	std::vector<unsigned int> indices;
	std::vector<glm::vec4> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;

	if (!loader::loadOBJ(path, indices, indexed_vertices, indexed_uvs, indexed_normals)) {
		logger::error("Failed to load .obj file \"%s\"!", path);
		return false;
	}

	//generate and fill buffer for indices
	glGenBuffers(1, &m_index_buffer_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

	//generate buffer for vertex data (vertices, uvs, normals)
	glGenBuffers(1, &m_vertex_buffer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);

	//allocate memory for vertex buffer
	glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(indexed_vertices) * sizeof(glm::vec4)
		+ sizeof(indexed_uvs) * sizeof(glm::vec2)
		+ sizeof(indexed_normals) * sizeof(glm::vec3),
		NULL, GL_STATIC_DRAW);

	//fill vertex buffer
	//vertex coordinates
	glBufferSubData(GL_ARRAY_BUFFER, 
		0,												//offset to 0
		sizeof(indexed_vertices)*sizeof(glm::vec4),		//size to size of vertex data
		&indexed_vertices[0]);							//data

	//uv coordinates
	glBufferSubData(GL_ARRAY_BUFFER, 
		sizeof(indexed_vertices) * sizeof(glm::vec4),	//offset to size of vertex data
		sizeof(indexed_uvs) * sizeof(glm::vec2),		//size to size of uv data
		&indexed_uvs[0]);								//data

	//normals
	glBufferSubData(GL_ARRAY_BUFFER, 
		sizeof(indexed_vertices) * sizeof(glm::vec4)	//offset to size of vertex data 
		+ sizeof(indexed_uvs) * sizeof(glm::vec2),		//	+size of uv data
		sizeof(indexed_vertices) * sizeof(glm::vec3),	//size to size of normal data
		&indexed_vertices[0]);							//data

	return true;
}

bool Mesh::initShaders()
{
	logger::debug("Loading Mesh-Shaders! This should only appear one time!");
	//load shaders and bind program
	program_ID = loader::LoadShaders("MeshShader.vs", "MeshShader.fs");
	if (program_ID == 0)
		return false;
	logger::debug("Successfully loaded Mesh-Shaders!");

	//get uniform locations
	uniform_loc_modelmatrix = glGetUniformLocation(program_ID, "model_matrix");
	uniform_loc_viewmatrix = glGetUniformLocation(program_ID, "view_matrix");
	uniform_loc_projectionmatrix = glGetUniformLocation(program_ID, "projection_matrix");
	uniform_loc_texsampler = glGetUniformLocation(program_ID, "tex_sampler");

	return true;
}

void Mesh::draw()
{
	//set model matrix
	glUniformMatrix4fv(uniform_loc_modelmatrix, 1, GL_FALSE, &m_model_matrix[0][0]);

	//bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture_ID);
	glUniform1i(uniform_loc_texsampler, 0);

	//bind vertex data buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);

	//vertex coordinates start at 0
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	glEnableVertexAttribArray(0);

	//uv coordinates start after vertex coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) (m_vertex_number * sizeof(glm::vec4)));
	glEnableVertexAttribArray(1);

	//normals start after uv coordinates
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*) (m_vertex_number * sizeof(glm::vec2) + m_vertex_number * sizeof(glm::vec2)));
	glEnableVertexAttribArray(2);

	//indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_ID);

	//draw elements
	glDrawElements(GL_TRIANGLES, m_vertex_number, GL_UNSIGNED_INT, (void*) 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Mesh::setViewMatrix(glm::mat4 view_matrix)
{
	glUniformMatrix4fv(uniform_loc_viewmatrix, 1, GL_FALSE, &view_matrix[0][0]);
}

void Mesh::setProjectionMatrix(glm::mat4 projection_matrix)
{
	glUniformMatrix4fv(uniform_loc_projectionmatrix, 1, GL_FALSE, &projection_matrix[0][0]);
}
