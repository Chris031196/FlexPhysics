#pragma once

#include "glm\glm.hpp"
#include <vector>

using namespace glm;

class FiniteElement
{

public:
	FiniteElement(vec3 position) : m_position(position) {};
	FiniteElement(vec3 position, vec3 movement) : m_position(position), m_movement(movement) {};
	FiniteElement(vec3 position, vec3 movement, vec3 static_force) : m_position(position), m_movement(movement), m_static_force(static_force) {};
	~FiniteElement();

	vec3 getPosition() const { return m_position; };
	vec3 getMovement() const { return m_movement; };

	void addImpulse(vec3 force);
	void addStaticForce(vec3 force);

	void update(float delta_time);
	
private:
	vec3 m_position;
	vec3 m_movement;
	vec3 m_static_force;
};

