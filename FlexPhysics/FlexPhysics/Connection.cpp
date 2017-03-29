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
	glm::vec3 force_1 = ((m_length - distance) * (pos_1 - pos_2));
	//force to be added on element 2
	glm::vec3 force_2 = ((m_length - distance) * (pos_2 - pos_1));

	//add impulses to the elements
	m_element_1->setStaticForce(force_1);
	m_element_2->setStaticForce(force_2);

	//update elements
	m_element_1->update(delta_time);
	m_element_2->update(delta_time);
}
