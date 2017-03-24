#include "DrawableElement.h"

GLuint DrawableElement::program_ID = 0;

DrawableElement::DrawableElement(Mesh * mesh)
{
	m_mesh = mesh;

	if (mesh == NULL) {
		if(program_ID == 0)
			if(!initShaders())
				throw MessageException("Failed to load Element Shader Program!");

		initVertexBuffer();
	}
}

DrawableElement::DrawableElement(float mass, vec3 position, vec3 movement, vec3 static_force, Mesh * mesh)
{
	m_mass = mass;
	m_position = position;
	m_movement = movement;
	m_static_force = static_force;
	m_mesh = mesh;
	if (mesh == NULL) {
		if (program_ID == 0)
			if (!initShaders())
				throw MessageException("Failed to load Element Shader Program!");

		initVertexBuffer();
	}
}

DrawableElement::~DrawableElement()
{
	if (m_mesh == 0) {
		glDeleteBuffers(1, &m_vertex_buffer_ID);
	}
}


bool DrawableElement::initShaders()
{
	logger::debug("Loading Element-Shaders! This should only appear one time!");
	program_ID = loader::LoadShaders("ElementShader.vs", "ElementShader.fs");
	if (program_ID == 0)
		return false;
	logger::debug("Successfully loaded Element-Shaders!");

	return true;
}

bool DrawableElement::initVertexBuffer()
{
	glGenBuffers(1, &m_vertex_buffer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &m_position[0], GL_STREAM_DRAW);

	return true;
}

void DrawableElement::draw()
{
	if (m_mesh == 0) {
		glUseProgram(program_ID);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), (void*) &m_position, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_POINTS, 0, 1);

		glDisableVertexAttribArray(0);
	}
	else {
		m_mesh->draw();
	}
}
