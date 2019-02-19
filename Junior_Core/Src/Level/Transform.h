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
	struct RenderJob;
	class Camera;

	class Transform : public Component
	{
	private:
		// Private Class Variables //
		// Local Transformation
		Mat3 localTransformation_;
		// Local Translation
		Vec3 localTranslation_;
		// Local Scaling
		Vec3 localScaling_;
		// Local Rotation
		float localRot_;
		// Whether the transformation matrix is dirty or not
		bool isDirty;
		// The object's camera
		Camera* camera_;

		// Private Member Functions //
		// Constructs a new transformation matrix based on the
		// local translation, scaling, and rotation
		void ReconstructTransformation();
	public:
		// Public Class Variables //
		RenderJob* job_;
		// Public Member Functions //
		// Constructor
		Transform();
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
	};
}