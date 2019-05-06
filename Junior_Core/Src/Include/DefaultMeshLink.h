#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: DefaultMeshLink.h
* Description: Links this game object to the DefaultMesh to render it on screen
* Created: 4 May 2018
* Last Modified: 4 May 2019
*/

// Includes
#include "Component.h"		// Components

namespace Junior
{
	// Forward Declarations
	struct RenderJob;
	class Transform;
	class Sprite;

	class DefaultMeshLink : public Component<DefaultMeshLink>
	{
	private:
		// Private Member Constants

		// The resource directory of the shader we are using
		const char* defaultProgramDir;
		// Private Member Variables

		// The job that takes care of the rendering data
		RenderJob* renderJob_;
		// The game object's transform
		Transform* transform_;
		// The game object's sprite
		Sprite* sprite_;

	public:
		// Public Member Functions

		// Default Constructor
		// Params:
		//	loadMesh: Whether we load the mesh data or not
		DefaultMeshLink(bool loadMeshData = false);
		// Copy Constructor
		// Params:
		//	other: The other mesh link we want to copy from
		DefaultMeshLink(const DefaultMeshLink& other);
		// Initializes the component
		void Initialize() override;
		// Updates the data to be rendered to the mesh
		// Params:
		//	dt: The time between frames
		void Update(double dt) override;
		// Unloads the component
		void Unload() override;
	};
}