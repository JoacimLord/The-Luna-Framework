#pragma once

#include "LfwAPI/Renderer/Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

namespace LFW {


	//This is used by the renderer to render 2D quads
	//Represents the data of 2D quads
	struct QuadVertex
	{
		glm::vec3 position;
		glm::vec3 colors;
		glm::vec2 texcoords;
	};

	//This is used by the renderer to render 2D quads
	//Represents the 2D quad
	struct QuadMesh
	{
		std::vector <QuadVertex> verticies;
		std::vector <GLuint> indicies;
		std::vector <Texture> textures;

		QuadMesh();
		QuadMesh(std::vector<QuadVertex>& verts);
		QuadMesh(std::vector<QuadVertex>& verts, std::vector<GLuint>& inds, std::vector<Texture>& texts);
	};

	//This is used by the renderer to render 2D quads
	//Stores and sets the data of the 2D quads
	struct QuadData
	{
		static QuadVertex quadVerts[];
		static GLuint quadInds[];
		static glm::vec2 textureCoordinates[];

		//Sets the verticies
		static void SetQuadData(QuadMesh& quadMesh);
	};
}
