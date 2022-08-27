#include "LFWpch.h"
#include "QuadMesh.h"

namespace LFW {

	QuadMesh::QuadMesh()
	{
		//Nothing for now
	}

	QuadMesh::QuadMesh(std::vector<QuadVertex>& verts)
	{
		verticies = verts;
	}
	QuadMesh::QuadMesh(std::vector<QuadVertex>& verts, std::vector<GLuint>& inds, std::vector<Texture>& texts)
	{
		verticies = verts;
		indicies = inds;
		textures = texts;
	}


	GLuint QuadData::quadInds[] =
	{
		 0, 2, 1,
		 0, 3, 2
	};

	glm::vec2 QuadData::textureCoordinates[] =
	{ 
		glm::vec2(0.0f, 0.0f), 
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f)
	};

	QuadVertex QuadData::quadVerts[] =
	{
		QuadVertex{ glm::vec3(-0.5f, -0.5f, 0.0f),   glm::vec3(1.0f, 0.0f, 0.0f),   textureCoordinates[0] },
		QuadVertex{ glm::vec3(0.5f, -0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 0.0f),   textureCoordinates[1] },
		QuadVertex{ glm::vec3(0.5f,  0.5f, 0.0f),   glm::vec3(1.0f, 0.0f, 1.0f),   textureCoordinates[2] },
		QuadVertex{ glm::vec3(-0.5f,  0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 1.0f),   textureCoordinates[3] },
	};

	void QuadData::SetQuadData(QuadMesh& quadMesh)
	{
		std::vector <QuadVertex> verts(quadVerts, quadVerts + sizeof(quadVerts) / sizeof(QuadVertex));
		quadMesh.verticies = verts;
	}
}