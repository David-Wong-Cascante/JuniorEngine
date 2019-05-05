#pragma once
/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: Mesh.h
 * Description: Meshes hold the data to render generic data to render sprites into the screen
				as well as custom data
 * Created: 1 May 2019
 * Last Modified: 2 May 2019
*/

// Includes
#include "Resource.h"		// Resources
#include <vector>			// Vector
#include <string>			// Strings

namespace Junior
{
	struct BasicData
	{
		// Public Static Variables

		// The size of each vertex of data (including any other data like texture data with it)
		const static unsigned TOTAL_SIZE= 5;
		// The size that fits the position of a vertex
		const static unsigned VERTEX_SIZE = 3;
		// The size that fits the texture coordinates
		const static unsigned TEXCOORD_SIZE = 2;


		// Public Member Variables

		// Vector of mesh vertices and texture coordinates swizzled together
		std::vector<float> data_;

		// Public Member Functions

		// Default Constructor
		BasicData();
		// Constructor
		// Params:
		//	count: The number of vertices we have
		//	vertices: The array of vertices
		//	textureCoordinates: The array of texture coordinates
		//	indices: The array of indices
		BasicData(unsigned count, const float* vertices, const float* textureCoodrinates);
		// Copy Constructor
		// Params:
		//	other: The other basic data we are trying to copy from
		BasicData(const BasicData& other);
	};

	class Mesh
	{
	private:
		// Private Member Data

		// The VAO of the mesh
		unsigned meshVertexArray_;
		// The basic vbo of the mesh
		unsigned meshBasicBuffer_;
		// The name of the mesh
		std::string name_;
		// Basic mesh data
		BasicData basicData_;

		// Private Member Functions

		// Sets up the initial data for the mesh
		void SetUpInitialData();

	public:
		// Public Static Variables
		// The start of the attributes for the mesh
		const static unsigned ATTRIBUTE_START_INDEX = 2;

		// Public Static Members

		// Returns a mesh object constructor with a default mesh
		static BasicData CreateQuadMeshData();

		// Public Member Functions

		// Default Consturctor
		Mesh(const std::string& name);
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
		Mesh(const std::string& name, unsigned count, const float* vertices, const float* textureCoordinates);
		// Constructs a mesh out of a basic data object
		// Params:
		//	basicData: The data we are passing into the mesh
		Mesh(const std::string& name, const BasicData& basicData);

		// Binds the vertex array object to OpenGL so that we can start updating the mesh in OpenGL
		void StartBinding();
		// Ends binding the mesh
		inline void EndBinding();

		// Virtual Functions

		// Virtual destructor because polymorphism
		virtual ~Mesh();
		// Draws the mesh to OpenGL
		virtual void Draw();

	protected:
		// Protected Member Functions

		// Cleans up the basic buffer and vertex objects
		void DeleteBufferData();
		// Sets the name of the mesh
		// Params:
		//	name: The name of the mesh
		void SetName(const std::string& name);
		// Set whether the basic vertex attributes are enabled or disabled
		// Params:
		//	enabled: Whether the attributes are enabled
		void SetBasicVertexAttribsEnabled(bool enabled) const;
	};
}