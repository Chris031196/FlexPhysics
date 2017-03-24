#include "FiniteElement.h"

FiniteElement::~FiniteElement()
{
}

void FiniteElement::addImpulse(glm::vec3 force)
{
	m_movement += (force / m_mass);
}

void FiniteElement::addStaticForce(glm::vec3 force)
{
	m_static_force += force;
}

void FiniteElement::update(float delta_time)
{
	m_position += (m_static_force / m_mass) * delta_time;
	m_position += m_movement * delta_time;
	m_movement *= 0.99f;
}
