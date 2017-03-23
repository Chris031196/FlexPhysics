#pragma once

#include "FiniteElement.h"
class Connection
{
public:
	Connection(
		float length, 
		float max_length, 
		float flexibility, 
		FiniteElement* element_1, 
		FiniteElement* element_2
	) : m_length(length), m_max_length(max_length), m_flexibility(flexibility), m_element_1(element_1), m_element_2(element_2) {};

	~Connection();

	/*
	*	calculates force vectors for the connected elements
	*	and adds them as impulses to them
	*/
	void calculateForces(float deltaTime);

private:
	float m_length;		// the distance the connection will try to keep between the elements
	float m_max_length;	// the distance at which the connection will break
	float m_flexibility;	// the flexibility of the connection (

	//the two elements in the connection
	FiniteElement* m_element_1;
	FiniteElement* m_element_2;
};

