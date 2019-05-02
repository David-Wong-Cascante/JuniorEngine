/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: Mesh.cpp
 * Description: Meshes hold the data to render generic data to render sprites into the screen
				as well as custom data
 * Created: 1 May 2019
 * Last Modified: 1 May 2019
*/

// Includes
#include "Mesh.h"

// Public Member Functions

Junior::BasicData::BasicData()
	: vertices_(), textureCoordinates_(), indices_()
{
}

Junior::BasicData::BasicData(unsigned count, const float* vertices, const float* textureCoordinates, 
							 const unsigned* indices)
	: vertices_(), textureCoordinates_(), indices_()
{
	// Reserve all the vectors
	vertices_.reserve(count * 3);
	textureCoordinates_.reserve(count * 2);
	indices_.reserve(count);
	// Copy all of the basic data
	for (size_t i = 0; i < count * 3; ++i)
	{
		vertices_.push_back(vertices[i]);
	}
	for (size_t i = 0; i < count * 2; ++i)
	{
		textureCoordinates_.push_back(textureCoordinates[i]);
	}
	for (size_t i = 0; i < count; ++i)
	{
		indices_.push_back(indices[i]);
	}
}

Junior::Mesh::Mesh()
	: basicData_(), meshVertexArray_(0), meshBasicBuffer_(0)
{
}

Junior::Mesh::Mesh(const Mesh& other)
	: meshVertexArray_(0), meshBasicBuffer_(0)
{
	// Copy over the data from the other mesh
	const std::vector<float>& otherVerts = other.basicData_.vertices_;
	for (auto begin = otherVerts.cbegin(); begin != otherVerts.cend(); ++begin)
	{
	}
}

Junior::Mesh::Mesh(unsigned count, const float* vertices, const float* textureCoordinates,
					const unsigned* indices)
	: basicData_(count, vertices, textureCoordinates, indices), meshVertexArray_(0), meshBasicBuffer_(0)
{
}

Junior::Mesh::Mesh(const BasicData& other)
	: basicData_(other.indices_.size(), other.vertices_.data(), other.textureCoordinates_.data(),
				 other.indices_.data()), meshVertexArray_(0), meshBasicBuffer_(0)
{
}