/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: Mesh.cpp
 * Description: Meshes hold the data to render generic data to render sprites into the screen
				as well as custom data
 * Created: 1 May 2019
 * Last Modified: 2 May 2019
*/

// Includes
#include "Mesh.h"
#include "OpenGLBundle.h"		// OpenGL Bundle

// Private Member Functions

void Junior::Mesh::StartBinding()
{
	// Bind the vertex array object
	glBindVertexArray(meshVertexArray_);
}

void Junior::Mesh::EndBinding()
{
	glBindVertexArray(0);
}

void Junior::Mesh::SetUpInitialData()
{
	// Delete any previous data if it existed
	glDeleteBuffers(1, &meshBasicBuffer_);
	glDeleteVertexArrays(1, &meshVertexArray_);

	// Set up the Vertex Array Object to draw the mesh
	glGenVertexArrays(1, &meshVertexArray_);
	glGenBuffers(1, &meshBasicBuffer_);

	// The buffer for all vertex data
	StartBinding();
	glBindBuffer(GL_ARRAY_BUFFER, meshBasicBuffer_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * basicData_.data_.size(), basicData_.data_.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<void*>(3 * sizeof(float)));

	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 0);

	// End the bind
	EndBinding();
}

// Public Static Functions

Junior::BasicData Junior::Mesh::CreateQuadMeshData()
{
	// Vertices
	float quadVertices[] = {
		-0.5f,-0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};

	// Texture Coordiantes
	float quadTexCoords[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
	};

	BasicData basic(4, quadVertices, quadTexCoords);
	return basic;
}

// Public Member Functions

Junior::BasicData::BasicData()
	: data_()
{
}

Junior::BasicData::BasicData(unsigned count, const float* vertices, const float* textureCoordinates)
	: data_()
{
	// Reserve the vector for the vertices (3) and texture coordinates (2)
	data_.reserve(count * TOTAL_SIZE);
	// Copy all of the basic data
	// The iterators for the data
	unsigned vertexIter = 0;
	unsigned textureCoordIter = 0;
	for (size_t i = 0; i < count; ++i)
	{
		// Copy over a vertex (three floats)
		for (size_t j = 0; j < VERTEX_SIZE; ++j)
		{
			data_.push_back(vertices[vertexIter++]);
		}

		// Copy over a texture coordinate (two floats)
		for (size_t j = 0; j < TEXCOORD_SIZE; ++j)
		{
			data_.push_back(textureCoordinates[textureCoordIter++]);
		}
	}
}

Junior::BasicData::BasicData(const BasicData& other)
{
	// Copy over the data from other to here
	data_.reserve(other.data_.size());
	for (auto iter = other.data_.cbegin(); iter != other.data_.cend(); ++iter)
	{
		data_.push_back(*iter);
	}
}

Junior::Mesh::Mesh(const std::string& name)
	: basicData_(), name_(name), meshVertexArray_(0), meshBasicBuffer_(0)
{
	SetUpInitialData();
}

Junior::Mesh::Mesh(const Mesh& other)
	: name_(other.name_), basicData_(other.basicData_), meshVertexArray_(other.meshVertexArray_), meshBasicBuffer_(other.meshBasicBuffer_)
{
}

Junior::Mesh::Mesh(const std::string& name, unsigned count, const float* vertices, const float* textureCoordinates)
	: basicData_(count, vertices, textureCoordinates), name_(name), meshVertexArray_(0), meshBasicBuffer_(0)
{
	SetUpInitialData();
}

Junior::Mesh::Mesh(const std::string& name, const BasicData& other)
	: basicData_(other), name_(name), meshVertexArray_(0), meshBasicBuffer_(0)
{
	SetUpInitialData();
}

Junior::Mesh::~Mesh()
{
	DeleteBufferData();
}

// Protected Member Functions

void Junior::Mesh::DeleteBufferData()
{
	glDeleteBuffers(1, &meshBasicBuffer_);
	glDeleteVertexArrays(1, &meshVertexArray_);
}

void Junior::Mesh::SetBasicVertexAttribsEnabled(bool enabled) const
{
	for (unsigned i = 0; i < ATTRIBUTE_START_INDEX; ++i)
	{
		if(enabled)
			glEnableVertexAttribArray(i);
		else
			glDisableVertexAttribArray(i);
	}
}

void Junior::Mesh::Draw(unsigned)
{
	// For this class, draw the singular mesh
	glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<unsigned>(basicData_.data_.size() / 5));
}

void Junior::Mesh::SetName(const std::string& name)
{
	name_ = name;
}