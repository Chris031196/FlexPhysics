#include "Connection.h"

Connection::~Connection()
{
}

void Connection::calculateForces(float delta_time)
{
	m_element_1->addStaticForce(glm::vec3(0.0f, 0.0f, 0.001f));

	m_element_1->update(delta_time);

	m_element_2->addStaticForce(glm::vec3(0.0f, 0.0f, -0.001f));

	m_element_2->update(delta_time);
}
