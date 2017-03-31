#include "Connection.h"

Connection::~Connection()
{
}

void Connection::calculateForces()
{
	//get positions and calculate distance between them
	glm::vec3 pos_1 = m_element_1->getPosition();
	glm::vec3 pos_2 = m_element_2->getPosition();
	float distance = glm::distance(pos_1, pos_2);
	float deviation = distance - m_length;
	float factor = deviation >= 0.0f ? -0.5f : 0.5f;

	pos_1 = glm::normalize(pos_1);
	pos_2 = glm::normalize(pos_2);

	//force to be added on element 1
	glm::vec3 force_1 = factor * (deviation*deviation * (pos_1 - pos_2)) / m_flexibility;
	//force to be added on element 2
	glm::vec3 force_2 = factor * (deviation*deviation * (pos_2 - pos_1)) / m_flexibility;

	//add impulses to the elements
	m_element_1->addImpulse(force_1);
	m_element_2->addImpulse(force_2);

	m_element_1->setStaticForce((pos_2 - pos_1) * deviation);
	m_element_2->setStaticForce((pos_1 - pos_2) * deviation);

	//resistance
	/*m_element_1->addImpulse((pos_2 - pos_1) * 0.1f);
	m_element_2->addImpulse((pos_1 - pos_2) * 0.1f);*/
}
