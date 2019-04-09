#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Camera.h
* Description: Holds the data for camera transformations and such as a component so that it can look at the object's transform
* Created: 18-Feb-2019
* Last Modified: 18-Feb-2019
*/

// Includes
#include "Component.h"				// Component
#include "Vec3.h"					// Vec3
#include "Mat3.h"					// Mat3 

namespace Junior
{
	// Enumeration to define the projection matrix
	enum ProjectionMode
	{
		ORTHOGRAPHIC, PERSPECTIVE
	};

	class Camera : public Component<Camera>
	{
		// Friend Classes
		friend class Transform;
	private:
		// The width and height of the camera
		float cameraWidth_;
		float cameraHeight_;
		// The near and far plane of the camera
		float nearPlane_;
		float farPlane_;
		// The projection matrix
		Mat3 projection_;
		// The camera transformation matrix
		Mat3 view_;
		// The projection mode
		ProjectionMode mode_;

		// Private Member Variables
		
		// Updates the camera's view matrix
		// Params:
		//	transformation: The transformation of the object
		void UpdateViewMatrix(const Mat3& transformation);
	public:
		// Public Member Functions
		
		// Constructor
		// Params:
		//	mode: The camera's projection mode
		//	cameraWidth: The camera's width in units
		//	cameraHeight: The camera's height in units
		//	nearPlane: The camera's near plane
		//	farPlane: The camera's far plane
		Camera(ProjectionMode mode = ProjectionMode::ORTHOGRAPHIC, float cameraWidth = 3.0f, float cameraHeight = 3.0f, float nearPlane = -5.0f, float farPlane = 5.0f	);
		// Hidden Copy Constructor
		// Params:
		//	other: The other camera we want to ccocpy from
		Camera(const Camera& other);
		// Initializes the component
		void Initialize() override;
		// Update the component
		// Params:
		//	dt: The time between frames
		void Update(double dt) override;
		// Shutsdown the component
		void Unload(MemoryManager* manager) override;
		// Updates the camera's projection matrix
		// Params:
		//	mode: The new projection mode
		//	cameraWidth: The new camera width
		//	cameraHeight: The new camera height
		//	zNear: The near Z plane
		//	zFar: The far Z plane
		void UpdateProjection(ProjectionMode mode, float cameraWidth, float cameraHeight, float zNear, float zFar);
		// Returns: The width of the camera
		float GetWidth() const;
		// Returns: The height of the camera
		float GetHeight() const;
		// Returns: The near Z plane of the camera
		float GetNearZPlane() const;
		// Returns: The far Z plane of the camera
		float GetFarZPlane() const;
		// Returns: The matrix with projection and camera transformation multiplied
		const Mat3 GetCameraMatrix();
		// Writes the component to a file
		// Params:
		//	parser: The parser used to write the component
		// Throws: ParserException
		void Serialize(Parser& parser) override;
		// Reads and creates an object from a file
		// Params:
		//	parser: The parser used to read the component from the file
		// Throws: ParserException
		void Deserialize(Parser& parser) override;
	};
}