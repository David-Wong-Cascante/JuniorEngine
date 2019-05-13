/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: ParticleMesh.cpp
 * Description: The mesh we are using to render the particles
 * Created: 10 May 2019
 * Last Modified: 10 May 2019
*/

// Includes
#include "ParticleMesh.h"
#include "OpenGLBundle.h"			// OpenGL Functions
#include "ParticleEmitter.h"		// Get the particle emitter

Junior::ParticleMesh::ParticleMesh()
	: Mesh("ParticleMesh", CreateQuadMeshData()), particleBuffer_(0), numParticleAttribs_(7)
{
	// Create the buffer for all the particle data
	glGenBuffers(1, &particleBuffer_);
	// Bind this meshes' vertex array object
	StartBinding();
	// Then, define a cleared buffer for the particle data
	glBindBuffer(GL_ARRAY_BUFFER, particleBuffer_);
	glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);
	// Start defining the partitions for the buffer
	// The position of the particle
	glEnableVertexAttribArray(Mesh::ATTRIBUTE_START_INDEX);
	glVertexAttribPointer(Mesh::ATTRIBUTE_START_INDEX, 4, GL_FLOAT, false, sizeof(Particle), reinterpret_cast<void*>(sizeof(Vec3) * 0));
	// The velocity of the particle
	glEnableVertexAttribArray(Mesh::ATTRIBUTE_START_INDEX + 1);
	glVertexAttribPointer(Mesh::ATTRIBUTE_START_INDEX + 1, 4, GL_FLOAT, false, sizeof(Particle), reinterpret_cast<void*>(sizeof(Vec3) * 1));
	// The color of the particle
	glEnableVertexAttribArray(Mesh::ATTRIBUTE_START_INDEX + 2);
	glVertexAttribPointer(Mesh::ATTRIBUTE_START_INDEX + 2, 4, GL_FLOAT, false, sizeof(Particle), reinterpret_cast<void*>(sizeof(Vec3) * 2));
	// The uv and scale of the particle
	glEnableVertexAttribArray(Mesh::ATTRIBUTE_START_INDEX + 3);
	glVertexAttribPointer(Mesh::ATTRIBUTE_START_INDEX + 3, 4, GL_FLOAT, false, sizeof(Particle), reinterpret_cast<void*>(sizeof(Vec3) * 3));
	// The size of the particle
	glEnableVertexAttribArray(Mesh::ATTRIBUTE_START_INDEX + 4);
	glVertexAttribPointer(Mesh::ATTRIBUTE_START_INDEX + 4, 1, GL_FLOAT, false, sizeof(Particle), reinterpret_cast<void*>(sizeof(Vec3) * 4));
	// The lifetime of thte particle
	glEnableVertexAttribArray(Mesh::ATTRIBUTE_START_INDEX + 5);
	glVertexAttribPointer(Mesh::ATTRIBUTE_START_INDEX + 5, 1, GL_FLOAT, false, sizeof(Particle), reinterpret_cast<void*>(sizeof(Vec3) * 4 + sizeof(float) * 1));
	// The particle's age
	glEnableVertexAttribArray(Mesh::ATTRIBUTE_START_INDEX + 6);
	glVertexAttribPointer(Mesh::ATTRIBUTE_START_INDEX + 6, 1, GL_FLOAT, false, sizeof(Particle), reinterpret_cast<void*>(sizeof(Vec3) * 4 + sizeof(float) * 2));
	
	// Set all of these particle properties to be used per particle, not per fragment/pixel
	for (size_t i = 0; i < numParticleAttribs_; ++i)
	{
		glVertexAttribDivisor(static_cast<GLsizei>(Mesh::ATTRIBUTE_START_INDEX + i), 1);
	}

	// Unbind the buffers so we don't intervene with other buffers and such
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	EndBinding();
}

Junior::ParticleMesh::~ParticleMesh()
{
	// Delete the particle buffer
	glDeleteBuffers(1, &particleBuffer_);
}

void Junior::ParticleMesh::Draw(unsigned shaderID)
{
	// Bind the mesh we are about to draw
	StartBinding();

	// Enable the vertex buffers' attributes
	SetBasicVertexAttribsEnabled(true);
	for (size_t i = 0; i < numParticleAttribs_; ++i)
	{
		glEnableVertexAttribArray(static_cast<GLsizei>(i + Mesh::ATTRIBUTE_START_INDEX));
	}

	// Start drawing the particles, list by list
	for (auto currEmitter = emitterParticleList_.begin(); currEmitter != emitterParticleList_.end(); ++currEmitter)
	{
		// Prepare an array to send to the GPU
		std::vector<Particle> particleData = (*currEmitter)->GetParticleList();
		// If all of the particles are indeed dead, then don't draw the particle list
		if ((*currEmitter)->GetNumParticlesAlive() == 0)
			continue;

		glBindBuffer(GL_ARRAY_BUFFER, particleBuffer_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * (*currEmitter)->GetNumParticlesAlive(), particleData.data(), GL_STREAM_DRAW);
		// Set the uniform for the texture atlas
		GLuint atlasID = glGetUniformLocation(shaderID, "textureAtlas");
		glUniform1i(atlasID, (*currEmitter)->textureAtlas_);
		// And DRAW
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, static_cast<GLsizei>(particleData.size()));
	}

	// Disable the vertex buffers' attributes
	SetBasicVertexAttribsEnabled(false);
	for (size_t i = 0; i < numParticleAttribs_; ++i)
	{
		glDisableVertexAttribArray(static_cast<GLsizei>(i + Mesh::ATTRIBUTE_START_INDEX));
	}
	// Unbind the mesh we are about to draw
	glBindBuffer(GL_ARRAY_BUFFER, particleBuffer_);
	EndBinding();
}

void Junior::ParticleMesh::AddList(ParticleEmitter* emitter)
{
	// Add the emitter to the list
	emitterParticleList_.push_back(emitter);
}