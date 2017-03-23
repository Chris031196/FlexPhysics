#include "Mesh.h"

Mesh::Mesh(char * obj_path, char * bmp_path)
{
	
	//initialize mesh
	bool success = false;
	if (obj_path != nullptr)
		success = initMesh(obj_path);
		
	if(!success)
		throw MessageException("Path to .obj file is empty!");

	//initialize texture
	if (bmp_path != nullptr)
		success = initTexture(bmp_path);
	else
		m_textureID = 0;
	
	//if texture loading fails, program continues without texture
	if (!success) {
		logger::error("Texturefile %s couldn't be loaded!", bmp_path);
		m_textureID = 0;
	}
}

Mesh::~Mesh()
{
}

bool Mesh::initTexture(char * path)
{


	return true;
}

bool Mesh::initMesh(char * path)
{
	std::vector<unsigned int> indices;
	std::vector<glm::vec4> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;

	loader::loadOBJ(path, indices, indexed_vertices, indexed_uvs, indexed_normals);

	return true;
}
