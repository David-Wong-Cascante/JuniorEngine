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

namespace Junior
{
	// Forward Declarations
	struct RenderJob;

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

	public:
		// Public Member Functions

		// Constructor
		DefaultMesh();
		// Virtual Destructor
		~DefaultMesh() override;
		// Updates the extra data into the mesh
		void UpdateExtraData() override;
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