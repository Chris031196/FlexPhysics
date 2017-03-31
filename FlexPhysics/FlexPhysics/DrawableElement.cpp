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
	m_force = static_force;
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
	glm::vec3 data[] = {
		m_position,					//position
		glm::vec3(1.0f, 1.0f, 1.0f)	//color (white)
	};
	glBufferData(GL_ARRAY_BUFFER, 2*sizeof(glm::vec3), &data[0], GL_STREAM_DRAW);

	return true;
}

void DrawableElement::draw()
{
	if (m_mesh == 0) {
		glUseProgram(program_ID);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3), &m_position[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) sizeof(glm::vec3));

		glDrawArrays(GL_POINTS, 0, 1);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	else {
		m_mesh->draw();
	}
}
