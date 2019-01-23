#pragma once
/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * Date Created: 1-May-2018
 * Last Modified: 11-Dec-2018
 * File name: Transform.h
 * Description: Declare the transform component, which is in charge of defining the final dimensions of the vertices in the game object
*/

// Includes //
#include "Component.h"
#include "Vec3.h"
#include "Mat3.h"

namespace Junior
{
	// Forward Declarations //
	//union Mat3;

	class Transform : public Component
	{
	private:
		// Private Class Variables //
		Mat3 localTransformation_;
		Vec3 localTranslation_;
		Vec3 localScaling_;
		float localRot_;
		bool isDirty;

		// Private Member Functions //
		// Constructs a new transformation matrix based on the
		// local translation, scaling, and rotation
		void ReconstructTransformation();
	public:
		// Public Class Variables //
		RenderJob* job;
		// Public Member Functions //
		// Constructor
		// Params:
		//	currGraphics: The graphics class used to render the world
		Transform(Graphics* currGraphics);
		// Initializes the component
		void Initialize();
		// Updates the transform
		// Params:
		//	ms: The delta time between frames
		void Update(double ms);
		// Cleans up the transform
		// Params:
		//	manager: The memory manager used to create this instance of the component
		void Clean(MemoryManager* manager);
		
		// Sets the local translatoin
		// Params:
		//	other: The translation to be set
		void SetLocalTranslation(const Vec3& other);
		// Sets the local scaling
		// Params:
		//	other: The scaling to be set
		void SetLocalScaling(const Vec3& other);
		// Sets the local rotatoin
		// Params:
		//	other: The rotation to be set
		void SetLocalRotation(const float other);
		
		// Returns: The local translation
		const Vec3& GetLocalTranslation() const;
		// Returns: The local scaling
		const Vec3& GetLocalScaling() const;
		// Returns: The local rotation
		const float GetLocalRotation() const;

		// Returns: The local transformation matrix
		const Mat3& GetLocalTransformation() const;
		// Returns: The global transformation matrix
		const Mat3 GetGlobalTransformation() const;

		// Returns: It's render job
		RenderJob* GetRenderJob() const;
	};
}