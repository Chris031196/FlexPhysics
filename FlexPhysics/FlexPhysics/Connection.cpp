#include "Connection.h"

Connection::~Connection()
{
}

void Connection::calculateForces(float delta_time)
{
	//get positions and calculate distance between them
	glm::vec3 pos_1 = m_element_1->getPosition();
	glm::vec3 pos_2 = m_element_2->getPosition();
	float distance = glm::distance(pos_1, pos_2);

	//force to be added on element 1
	glm::vec3 force_1 = glm::vec3(0.0f);
	//force to be added on element 2
	glm::vec3 force_2 = glm::vec3(0.0f);

	//is the distance too long or too short?
	if (distance >= m_length) {
		force_1 = ((distance - m_length) * (pos_2 - pos_1)) / m_flexibility;

		force_2 = ((distance - m_length) * (pos_1 - pos_2)) / m_flexibility;
	}
	else {
		force_1 = ((m_length - distance) * (pos_1 - pos_2)) / m_flexibility;

		force_2 = ((m_length - distance) * (pos_2 - pos_1)) / m_flexibility;
	}

	//add impulses to the elements
	m_element_1->addImpulse(force_1);
	m_element_2->addImpulse(force_2);

	//update elements
	m_element_1->update(delta_time);
	m_element_2->update(delta_time);
}
