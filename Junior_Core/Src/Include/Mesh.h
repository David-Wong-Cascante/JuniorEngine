#pragma once
/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: Mesh.h
 * Description: Meshes hold the data to render generic data to render sprites into the screen
				as well as custom data
 * Created: 1 May 2019
 * Last Modified: 1 May 2019
*/

// Includes
#include <vector>			// Vector

namespace Junior
{
	struct BasicData
	{
		// Public Member Variables

		// Vector of mesh vertices
		std::vector<float> vertices_;
		// Floats of texture coordinates
		std::vector<float> textureCoordinates_;
		// Indices for the vertices
		std::vector<unsigned> indices_;

		// Public Member Functions

		// Default Constructor
		BasicData();
		// Constructor
		// Params:
		//	count: The number of vertices we have
		//	vertices: The array of vertices
		//	textureCoordinates: The array of texture coordinates
		//	indices: The array of indices
		BasicData(unsigned count, const float* vertices, const float* textureCoodrinates, const unsigned* indices);
	};

	class Mesh
	{
	private:
		// Private Member Data

		// Basic mesh data
		BasicData basicData_;
		// The VAO of the mesh
		unsigned meshVertexArray_;
		// The basic vbo of the mesh
		unsigned meshBasicBuffer_;
	public:
		// Public Member Functions

		// Default Consturctor
		Mesh();
		// Copy Constructor
		// Params:
		//	other: The other mesh we are copying from
		Mesh(const Mesh& other);
		// Constructs a mesh out of data
		// Params:
		//	count: The number of vertices we have
		//	vertices: The vertices we put in
		//	textureCoords: The texture coordinates we put in
		//	indices: The indices we put in
		Mesh(unsigned count, const float* vertices, const float* textureCoordinates, const unsigned* indices);
		// Constructs a mesh out of a basic data object
		// Params:
		//	basicData: The data we are passing into the mesh
		Mesh(const BasicData& basicData);
		// Binds the mesh to OpenGL
		void Bind();
	};
}