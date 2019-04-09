/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Camera.h
* Description: Describes how the camera works
* Created: 18-Feb-2019
* Last Modified: 18-Feb-2019
*/

// Includes
#include "Camera.h"				// Camera
#include "Graphics.h"			// Graphics
#include "MemoryManager.h"		// Memory Manager
#include "LinearMath.h"			// Linear Math Operations

// Private Member Functions
void Junior::Camera::UpdateViewMatrix(const Junior::Mat3& transformation)
{
	// Assuming the matrix is indeed a transformation matrix, then we can it to decipher the object's translation and rotation
	float translationX = transformation.m03_;
	float translationY = transformation.m13_;
	// Get the x scale using the method found here: https://math.stackexchange.com/questions/237369/given-this-transformation-matrix-how-do-i-decompose-it-into-translation-rotati
	float xScale = Length(Vec3(transformation.m00_, transformation.m01_, transformation.m02_, 0));
	// Get the rotation by dividing the first element of the matrix by the x scale
	float cosAngle = transformation.m00_ / xScale;
	float angle = acosf(cosAngle);
	// Finally, build the view matrix for the camera (based on this blog post: http://www.david-amador.com/2013/07/opengl-camera-2d-with-zoom-and-rotation/)
	// Same first name as me... huh
	view_ = Translation(Vec3(-translationX, -translationY)) * Rotation(angle);
}

// Public Member Functions

Junior::Camera::Camera(Junior::ProjectionMode mode, float cameraWidth, float cameraHeight, float zNear, float zFar)
	: Component("Camera"), view_(Identity())
{
	UpdateProjection(mode, cameraWidth, cameraHeight, zNear, zFar);
}

Junior::Camera::Camera(const Camera& other)
	: Component("Camera"), mode_(other.mode_), cameraWidth_(other.cameraWidth_), cameraHeight_(other.cameraHeight_), nearPlane_(other.nearPlane_),
	farPlane_(other.farPlane_)
{
}

void Junior::Camera::Initialize()
{
	// Create the projection matrix
}

void Junior::Camera::Update(double dt)
{

}

void Junior::Camera::Unload(MemoryManager* manager)
{
}

void Junior::Camera::UpdateProjection(ProjectionMode mode, float cameraWidth, float cameraHeight, float zNear, float zFar)
{
	mode_ = mode;
	cameraWidth_ = cameraWidth;
	cameraHeight_ = cameraHeight;
	nearPlane_ = zNear;
	farPlane_ = zFar;

	switch (mode)
	{
	case Junior::ORTHOGRAPHIC:
		projection_ = Orthographic(-cameraWidth_/2.0f, cameraWidth_/2.0f, cameraHeight_/2.0f, -cameraHeight_/2.0f, zNear, zFar);
		break;
	case Junior::PERSPECTIVE:
		// TODO: Make perspective work!
		break;
	default:
		break;
	}
}

float Junior::Camera::GetWidth() const
{
	return cameraWidth_;
}

float Junior::Camera::GetHeight() const
{
	return cameraHeight_;
}

float Junior::Camera::GetNearZPlane() const
{
	return nearPlane_;
}

float Junior::Camera::GetFarZPlane() const
{
	return farPlane_;
}

const Junior::Mat3 Junior::Camera::GetCameraMatrix()
{
	return (projection_ * view_);
}

void Junior::Camera::Serialize(Parser& parser)
{
}

void Junior::Camera::Deserialize(Parser& parser)
{
}