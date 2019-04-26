#pragma once
/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * Date Created: 1 May 2018
 * Last Modified: 26 Apr 2019
 * File name: Transform.h
 * Description: Declare the transform component, which is in charge of defining the final dimensions of the vertices in the game object
*/

// Includes //
#include "Component.h"				// Component
#include "Vec3.h"					// Vector3
#include "Mat3.h"					// Matrix3

namespace Junior
{
	// Forward Declarations //
	struct RenderJob;
	class Camera;

	class Transform : public Component<Transform>
	{
	private:
		// Private Class Variables
		// Local Transformation
		Mat3 localTransformation_;
		// Local Translation
		Vec3 localTranslation_;
		// Local Scaling
		Vec3 localScaling_;
		// Local Rotation
		float localRot_;
		// Whether the transformation matrix is dirty or not
		bool isDirty_;
		// The object's camera
		Camera* camera_;
		// The game object's render job
		RenderJob* job_;

		// Private Member Functions //
		// Constructs a new transformation matrix based on the
		// local translation, scaling, and rotation
		void ReconstructTransformation();
	public:
		// Public Class Variables //
		// Public Member Functions //

		// Constructor
		Transform();
		// Protected Member Functions
		// Copy constructor
		// Params:
		//	other: The other transform
		Transform(const Transform& other);
		// Initializes the component
		void Initialize() override;
		// Updates the transform
		// Params:
		//	ms: The delta time between frames
		void Update(double ms) override;
		// Cleans up the transform
		// Params:
		//	manager: The memory manager used to create this instance of the component
		void Unload() override;
		
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
		// Writes the component to a file
		// Params:
		//	parser: The parser used to write the component
		// Throws: ParserException
		void Serialize(Parser& parser) const override;
		// Reads and creates an object from a file
		// Params:
		//	parser: The parser used to read the component from the file
		// Throws: ParserException
		void Deserialize(Parser& parser) override;
	};
}