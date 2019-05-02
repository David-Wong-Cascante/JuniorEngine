/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: DefaultMesh.cpp
 * Description: The default mesh that objects use when they don't specify a particular mesh
 * Created: 2 May 2019
 * Last Modified: 2 May 2019
*/

// Includes
#include "DefaultMesh.h"
#include "RenderJob.h"

// Public Member Functions

Junior::DefaultMesh::DefaultMesh()
	: Mesh(Mesh::CreateQuadMesh())
{
	// The buffer for all render job data
	glBindBuffer(GL_ARRAY_BUFFER, jobsBufferObject_);
	glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);

	// Transformation Matrix
	// We have four vectors per matrix, so we are setting one vector per time
	for (unsigned matrixPart = 0; matrixPart < 4; ++matrixPart)
	{
		glEnableVertexAttribArray(Mesh::ATTRIBUTE_START_INDEX + matrixPart);
		glVertexAttribPointer(Mesh::ATTRIBUTE_START_INDEX, 4, GL_FLOAT, GL_FALSE, 
			sizeof(RenderJob), reinterpret_cast<void*>(sizeof(float) * (matrixPart + 1) * 4));
	}

	// UV Coordinate Modification Data
	glEnableVertexAttribArray(Mesh::ATTRIBUTE_START_INDEX + 4);
	glVertexAttribPointer(Mesh::ATTRIBUTE_START_INDEX + 4, 4, GL_FLOAT, GL_FALSE, sizeof(RenderJob), reinterpret_cast<void*>(sizeof(float) * 4 * 4));

	// Texture Selection Data
	glEnableVertexAttribArray(Mesh::ATTRIBUTE_START_INDEX + 5);
	glVertexAttribPointer(Mesh::ATTRIBUTE_START_INDEX + 4, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(RenderJob), reinterpret_cast<void*>(sizeof(float) * 5 * 4));

	// Set the attribute divisors
	for (unsigned i = 0; i <= NUM_ATTRIBUTES; ++i)
	{
		glVertexAttribDivisor(Mesh::ATTRIBUTE_START_INDEX + i, 1);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	EndBinding();
}

Junior::DefaultMesh::~DefaultMesh()
{
	ClearJobs();
}

void Junior::DefaultMesh::UpdateExtraData()
{
	// Fill in the render job data
	glBindBuffer(GL_ARRAY_BUFFER, jobsBufferObject_);
	glBufferData(GL_ARRAY_BUFFER, jobsBufferObject_, nullptr, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, renderJobs_.size(), renderJobs_.data());
}

void Junior::DefaultMesh::Draw()
{
	// Bind the mesh to OpenGL
	StartBinding();
	// Enable all of the attributes
	SetBasicVertexAttribsEnabled(true);
	for (unsigned i = 0; i <= NUM_ATTRIBUTES; ++i)
	{
		glEnableVertexAttribArray(i);
	}

	// Draw all of the objects sharing this mesh
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, static_cast<GLsizei>(renderJobs_.size()));

	// Disable all of the attributes
	SetBasicVertexAttribsEnabled(false);
	for (unsigned i = 0; i <= NUM_ATTRIBUTES; ++i)
	{
		glDisableVertexAttribArray(i);
	}
	// End the binding
	EndBinding();
}

Junior::RenderJob* Junior::DefaultMesh::GetNewRenderJob()
{
	RenderJob* renderJob = new RenderJob;
	renderJobs_.push_back(renderJob);
	return renderJob;
}

void Junior::DefaultMesh::RemoveRenderJob(const RenderJob* renderJob)
{
	for (auto iter = renderJobs_.cbegin(); iter != renderJobs_.cend(); ++iter)
	{
		if ((*iter) == renderJob)
		{
			renderJobs_.erase(iter);
			return;
		}
	}
}

void Junior::DefaultMesh::ClearJobs()
{
	// Delete all of the render jobs we have allocated
	for (auto iter = renderJobs_.cbegin(); iter != renderJobs_.cend(); ++iter)
	{
		delete (*iter);
	}

	renderJobs_.clear();
}