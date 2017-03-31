#pragma once

#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp"
#include <vector>

using namespace glm;

class FiniteElement
{

public:
	FiniteElement() : m_mass(1.0f), m_position(glm::vec3(0)), m_movement(glm::vec3(0)), m_force(glm::vec3(0)) {};
	FiniteElement(float mass, vec3 position, vec3 movement, vec3 static_force) : m_mass(mass), m_position(position), m_movement(movement), m_force(static_force) {};
	~FiniteElement();

	vec3 getPosition() const { return m_position; };
	vec3 getMovement() const { return m_movement; };

	void addImpulse(vec3 force);
	void setStaticForce(vec3 force);

	void update(float delta_time);
	
protected:
	vec3 m_position;
	vec3 m_movement;
	vec3 m_force;
	float m_mass;
};