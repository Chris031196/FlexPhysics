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
	//m_elements.push_back(new DrawableElement(1.0f, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), NULL));
	for (int i = 0; i < elements.size(); i++) {
		bool alreadyIn = false;
		for (int j = 0; j < m_elements.size(); j++) {
			if (elements[i] == m_elements[j]->getPosition()) {
				alreadyIn = true;
				continue;
			}
		}
		if(!alreadyIn)
			m_elements.push_back(new DrawableElement(1.0f, elements[i], glm::vec3(0.0f), glm::vec3(0.0f), NULL));
	}
	
	//initialize connections
	for (int i = 0; i < m_elements.size(); i++) {

		float closeDist[] = { 
			glm::distance(m_elements[i]->getPosition(), m_elements[0]->getPosition()),
			glm::distance(m_elements[i]->getPosition(), m_elements[1]->getPosition()),
			glm::distance(m_elements[i]->getPosition(), m_elements[2]->getPosition()),
			glm::distance(m_elements[i]->getPosition(), m_elements[3]->getPosition())
		};

		int closeIndex[] = {
			0,
			1,
			2,
			3
		};

		float farDist[] = {
			glm::distance(m_elements[i]->getPosition(), m_elements[0]->getPosition()),
			glm::distance(m_elements[i]->getPosition(), m_elements[1]->getPosition()),
			glm::distance(m_elements[i]->getPosition(), m_elements[2]->getPosition()),
			glm::distance(m_elements[i]->getPosition(), m_elements[3]->getPosition())
		};

		int farIndex[] = {
			0,
			1,
			2,
			3
		};

		for (int j = 4; j < m_elements.size(); j++) {
			float curDist = glm::distance(m_elements[i]->getPosition(), m_elements[j]->getPosition());
			if (closeDist[0] == 0.0f || curDist < closeDist[0] && curDist > 0.0f) {
				closeDist[0] = curDist;
				closeIndex[0] = j;
			}
			else if (closeDist[1] == 0.0f || curDist < closeDist[1] && curDist > 0.0f) {
				closeDist[1] = curDist;
				closeIndex[1] = j;
			}
			else if (closeDist[2] == 0.0f || curDist < closeDist[2] && curDist > 0.0f) {
				closeDist[2] = curDist;
				closeIndex[2] = j;
			}
			else if (closeDist[3] == 0.0f || curDist < closeDist[3] && curDist > 0.0f) {
				closeDist[3] = curDist;
				closeIndex[3] = j;
			}
			else if(farDist[0] == 0.0f || curDist > farDist[0] && curDist > 0.0f) {
				farDist[0] = curDist;
				farIndex[0] = j;
			}
			else if (farDist[1] == 0.0f || curDist > farDist[1] && curDist > 0.0f) {
				farDist[1] = curDist;
				farIndex[1] = j;
			}
			else if (farDist[2] == 0.0f || curDist > farDist[2] && curDist > 0.0f) {
				farDist[2] = curDist;
				farIndex[2] = j;
			}
			else if (farDist[3] == 0.0f || curDist > farDist[3] && curDist > 0.0f) {
				farDist[3] = curDist;
				farIndex[3] = j;
			}
		}
		m_connections.push_back(new DrawableConnection(closeDist[0], 3.0f, m_flexibility, m_elements[i], m_elements[closeIndex[0]], m_elements[0]->getProgram()));
		m_connections.push_back(new DrawableConnection(closeDist[1], 3.0f, m_flexibility, m_elements[i], m_elements[closeIndex[1]], m_elements[0]->getProgram()));
		m_connections.push_back(new DrawableConnection(closeDist[2], 3.0f, m_flexibility, m_elements[i], m_elements[closeIndex[2]], m_elements[0]->getProgram()));
		m_connections.push_back(new DrawableConnection(closeDist[3], 3.0f, m_flexibility, m_elements[i], m_elements[closeIndex[3]], m_elements[0]->getProgram()));
		m_connections.push_back(new DrawableConnection(farDist[0], 3.0f, m_flexibility, m_elements[i], m_elements[farIndex[0]], m_elements[0]->getProgram()));
		m_connections.push_back(new DrawableConnection(farDist[1], 3.0f, m_flexibility, m_elements[i], m_elements[farIndex[1]], m_elements[0]->getProgram()));
		m_connections.push_back(new DrawableConnection(farDist[2], 3.0f, m_flexibility, m_elements[i], m_elements[farIndex[2]], m_elements[0]->getProgram()));
		m_connections.push_back(new DrawableConnection(farDist[3], 3.0f, m_flexibility, m_elements[i], m_elements[farIndex[3]], m_elements[0]->getProgram()));
	}
	//for (int i = 1; i < m_elements.size(); i++) {
	//	m_connections.push_back(new DrawableConnection(glm::distance(m_elements[i]->getPosition(), glm::vec3(0.0f)), 3.0f, m_flexibility, m_elements[i], m_elements[0], m_elements[0]->getProgram()));
	//}

}

void FlexObject::update(float delta_time)
{
	for (int i = 0; i < m_connections.size(); i++) {
		m_connections[i]->calculateForces();
	}
	for (int i = 0; i < m_elements.size(); i++) {
		// -- gravity --
		m_elements[i]->addForce(glm::vec3(0.0f, -0.01f, 0.0f));
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


