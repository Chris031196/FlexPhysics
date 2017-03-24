#pragma once

#include "glew.h"
#include "Connection.h"
class DrawableConnection : public Connection
{
public:
	DrawableConnection(
		float length,
		float max_length,
		float flexibility,
		FiniteElement* element_1,
		FiniteElement* element_2,
		GLuint program_ID
	) : Connection(length, max_length, flexibility, element_1, element_2), m_program_ID(program_ID) {
		initVertexBuffer();
	};
	~DrawableConnection();

	void draw();

private:
	GLuint m_vertex_buffer_ID;
	GLuint m_program_ID;
	bool initVertexBuffer();
};

