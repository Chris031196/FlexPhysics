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
	if (m_position.y <= -10.0f) {
		m_position.y = -9.99999999f;
		addForce(glm::vec3(-m_movement.x, -m_movement.y, -m_movement.z) * m_mass);
	}
	m_movement += m_force / m_mass;
	m_position += m_movement * delta_time;
	m_force = glm::vec3(0.0f);
}
