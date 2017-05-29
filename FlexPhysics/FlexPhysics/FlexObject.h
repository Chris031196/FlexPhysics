#pragma once

#include "glm\glm.hpp"
#include "DrawableConnection.h"
#include "DrawableElement.h"
#include <vector>

enum Connection_Type { SOLID, TRIANGLES, LINES };

class FlexObject
{
public:
	FlexObject(Connection_Type type, float flexibility);
	~FlexObject();

	void init(std::vector<glm::vec3> elements);
	void update(float delta_time);

	DrawableElement* getElement(int index) { return m_elements[index]; };

private:
	Connection_Type m_type;
	std::vector<DrawableConnection*> m_connections;
	std::vector<DrawableElement*> m_elements;
	float m_flexibility;
};

