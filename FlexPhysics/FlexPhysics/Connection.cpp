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
	float factor = deviation >= 0.0f ? -1.0f : 1.0f;

	//force to be added on element 1
	glm::vec3 force_1 = factor * (deviation*deviation * glm::normalize(pos_1 - pos_2)) / m_flexibility;
	//force to be added on element 2
	glm::vec3 force_2 = factor * (deviation*deviation * glm::normalize(pos_2 - pos_1)) / m_flexibility;

	//add impulses to the elements
	m_element_1->addForce(force_1);
	m_element_2->addForce(force_2);


	// ----- calculate resistance of connection ----- \\
	//get movement vectors
	vec3 mov_1 = vec3(m_element_1->getMovement());
	vec3 mov_2 = vec3(m_element_2->getMovement());

	//calculate the movement vector relative to the other element
	vec3 comp_1 = (mov_1 - mov_2) / 2.0f;
	mov_1 -= comp_1;

	vec3 comp_2 = (mov_2 - mov_1) / 2.0f;
	mov_2 -= comp_2;

	m_element_1->addForce(-(0.005f + (0.01f / m_flexibility)) * comp_1 * m_element_1->getMass());
	m_element_1->addForce(-(0.005f + (0.01f / m_flexibility)) * comp_1 * m_element_1->getMass());
	//m_element_1->setMovement(mov_1);
	//m_element_2->setMovement(mov_2);
}
