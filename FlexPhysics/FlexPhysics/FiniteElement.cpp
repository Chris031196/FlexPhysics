#include "FiniteElement.h"

FiniteElement::~FiniteElement()
{

}

void FiniteElement::addForce(glm::vec3 force)
{
	m_force += force;
}

void FiniteElement::setStaticForce(glm::vec3 force)
{
	m_movement += (force / m_mass);
}

void FiniteElement::update(float delta_time)
{
	m_movement += m_force / m_mass;
	m_position += m_movement * delta_time;
	m_force = glm::vec3(0.0f);
}
