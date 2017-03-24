#pragma once
#include "FiniteElement.h"
#include "Mesh.h"

class DrawableElement : public FiniteElement
{
public:
	DrawableElement(Mesh* mesh);
	DrawableElement(float mass, vec3 position, vec3 movement, vec3 static_force, Mesh* mesh);
	~DrawableElement();

	void draw();
	GLuint getProgram() { return program_ID; };
	
private:
	Mesh* m_mesh = 0;
	GLuint m_vertex_buffer_ID;

	static GLuint program_ID;
	bool initShaders();
	bool initVertexBuffer();
};

