#pragma once
/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: DefaultMesh.h
 * Description: The default mesh that objects use when they don't specify a particular mesh
 * Created: 2 May 2019
 * Last Modified: 2 May 2019
*/

// Includes
#include <Mesh.h>
#include "RenderJob.h"			// Render Job

namespace Junior
{
	class DefaultMesh : public Mesh
	{
	private:
		// Private Static Member Functions
		// The number of attributes we have in this class
		const static unsigned NUM_ATTRIBUTES = 5;

		// Private Member Functions

		// The buffer object for the render jobs
		unsigned jobsBufferObject_;
		// A vector that holds the extra data of all of the objects that are using it
		std::vector<RenderJob*> renderJobs_;
		// The vector that translates our render jobs from poiners to actual data
		std::vector<RenderJob> readyToRenderJobs_;

	public:
		// Public Member Functions

		// Constructor
		DefaultMesh();
		// Virtual Destructor
		~DefaultMesh() override;
		// Draws the mesh to OpenGL
		void Draw() override;
		// Assigns a new render job
		// Returns: The new render job we just assigned
		RenderJob* GetNewRenderJob();
		// Removes a render job from the mesh
		// Params:
		//	renderJob: The render job we are trying to remove
		void RemoveRenderJob(const RenderJob* renderJob);
		// Clears all of the render jobs we have
		void ClearJobs();
	};
}