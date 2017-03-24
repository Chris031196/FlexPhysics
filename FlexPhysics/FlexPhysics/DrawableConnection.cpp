#include "DrawableConnection.h"

DrawableConnection::~DrawableConnection()
{
	glDeleteBuffers(1, &m_vertex_buffer_ID);
}


bool DrawableConnection::initVertexBuffer()
{
	glGenBuffers(1, &m_vertex_buffer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);

	glm::vec3 pos_1 = m_element_1->getPosition();
	glm::vec3 pos_2 = m_element_2->getPosition();
	glm::vec3 color = glm::vec3(glm::distance(pos_1, pos_2) - m_length, 0.1f, 0.1f);
	glm::vec3 data[] = {
		pos_1,	//position of first element
		pos_2,	//position of second element
		color,	//color of the connection
		color
	};
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec3), &data[0], GL_STREAM_DRAW);
	return false;
}


void DrawableConnection::draw()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
	glm::vec3 pos_1 = m_element_1->getPosition();
	glm::vec3 pos_2 = m_element_2->getPosition();
	glm::vec3 color = glm::vec3(glm::distance(pos_1, pos_2) - m_length, 0.1f, 0.1f);
	glm::vec3 data[] = {
		pos_1,	//position of first element
		pos_2,	//position of second element
		color,	//color of the connection
		color
	};
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec3), &data[0], GL_STREAM_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) (2* sizeof(glm::vec3)));

	glDrawArrays(GL_LINES, 0, 2);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}