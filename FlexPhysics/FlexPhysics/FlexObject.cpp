#include "FlexObject.h"


FlexObject::FlexObject(Connection_Type type, float flexibility)
{
	m_type = type;
	m_flexibility = flexibility;
}


FlexObject::~FlexObject()
{
	for (int i = 0; i < m_connections.size(); i++) {
		delete m_connections[i];
	}
	for (int i = 0; i < m_elements.size(); i++) {
		delete m_elements[i];
	}
}

void FlexObject::init(std::vector<glm::vec3> elements)
{
	//initialize elements
	for (int i = 0; i < elements.size(); i++) {
		m_elements.push_back(new DrawableElement(1.0f, elements[i], glm::vec3(0.0f), glm::vec3(0.0f), NULL));
	}
	
	//initialize connections
	for (int i = 0; i < m_elements.size(); i++) {
		for (int j = 0; j < m_elements.size(); j++) {
			if (j != i) {
				m_connections.push_back(new DrawableConnection(glm::distance(m_elements[i]->getPosition(), m_elements[j]->getPosition()), 3.0f, m_flexibility, m_elements[i], m_elements[j], m_elements[0]->getProgram()));
			}
		}
	}
}

void FlexObject::update(float delta_time)
{
	for (int i = 0; i < m_connections.size(); i++) {
		m_connections[i]->calculateForces();
	}
	for (int i = 0; i < m_elements.size(); i++) {
		// -- gravity --
		m_elements[i]->addForce(glm::vec3(0.0f, -0.1f, 0.0f));
		// -- gravity --

		m_elements[i]->update(delta_time);
	}
	for (int i = 0; i < m_elements.size(); i++) {
		m_elements[i]->draw();
	}
	for (int i = 0; i < m_connections.size(); i++) {
		m_connections[i]->draw();
	}
}


