/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* Date Created: 1 May 2018
* Last Modified: 18 Apr 2019
* File name: Transform.cpp
* Description: The Transform data type really just holds data about the Transform, we are going
*	to define the constructor to 
*/

// Includes //
#include "Transform.h"

#include "RenderJob.h"			// Render Job
#include "GameObject.h"			// Game Object
#include "Graphics.h"			// Graphics
#include "Vec3.h"				// Vec3
#include "LinearMath.h"			// Linear Math, Helper Functions
#include "Camera.h"				// Camera
#include "Parser.h"				// Parse

// Public Member Functions

Junior::Transform::Transform()
	: Component(), localRot_(0.0f), localTranslation_({ 0, 0, 0, 1 }), localScaling_({ 1, 1, 1, 0 }), isDirty_(true)
{
}

Junior::Transform::Transform(const Transform& other)
	: Component(), localRot_(other.localRot_), localTranslation_(other.localTranslation_), localScaling_(other.localScaling_),
	localTransformation_(other.localTransformation_), isDirty_(true)
{
}

void Junior::Transform::Initialize()
{
	updateable_ = true;
	isDirty_ = true;
	// Find the owner's camera
	camera_ = owner_->GetComponent<Camera>();
	job_ = owner_->GetRenderJob();
	ReconstructTransformation();
}

void Junior::Transform::Update(double ms)
{
	// Reconstruct the matrix if necessary
	ReconstructTransformation();
	Mat3 transformation = GetGlobalTransformation();
	if (job_)
	{
		// Set the render jobs matrix pointer
		job_->transformation_ = transformation;
	}
}

void Junior::Transform::Unload()
{
}

void Junior::Transform::SetLocalTranslation(const Vec3& other)
{
	if (other.x_ == localTranslation_.x_ && other.y_ == localTranslation_.y_ && other.z_ == localTranslation_.z_)
		return;

	isDirty_ = true;
	localTranslation_ = other;
}

void Junior::Transform::SetLocalScaling(const Vec3& other)
{
	if (other.x_ == localScaling_.x_ && other.y_ == localScaling_.y_ && other.z_ == localScaling_.z_)
		return;

	isDirty_ = true;
	localScaling_ = other;
}

void Junior::Transform::SetLocalRotation(const float other)
{
	if (other == localRot_)
		return;

	isDirty_ = true;
	localRot_ = other;
}

const Junior::Vec3& Junior::Transform::GetLocalTranslation() const
{
	return localTranslation_;
}

const Junior::Vec3& Junior::Transform::GetLocalScaling() const
{
	return localScaling_;
}

const float Junior::Transform::GetLocalRotation() const
{
	return localRot_;
}

const Junior::Mat3& Junior::Transform::GetLocalTransformation() const
{
	return localTransformation_;
}

const Junior::Mat3 Junior::Transform::GetGlobalTransformation() const
{
	Mat3 globalTransformation = Identity();
	if (owner_)
	{
		// Get the parent of the object
		GameObject* parent = owner_->GetParent();
		// If the transform component exists on the parent, then multiply this transformation by the parent's transform
		if (parent)
		{
			Transform* parentTransform = parent->GetComponent<Transform>();
			if (parentTransform)
			{
				globalTransformation = parentTransform->GetGlobalTransformation();
			}
		}
	}
	// Total Transformation
	Mat3 totalTransformation = globalTransformation * localTransformation_;
	// Set the camera's view matrix
	if (camera_)
		camera_->UpdateViewMatrix(totalTransformation);

	return totalTransformation;
}

void Junior::Transform::Serialize(Parser& parser)
{
	// Serialize transform components
	// Not the matrix though, we just construct that
	parser.WriteVariable("localTranslation", localTranslation_);
	parser.WriteVariable("localRotation", localRot_);
	parser.WriteVariable("localScaling", localScaling_);
}

void Junior::Transform::Deserialize(Parser& parser)
{
	// Deserialize the transform
	parser.ReadVariable("localTranslation", localTranslation_);
	parser.ReadVariable("localRotation", localRot_);
	parser.ReadVariable("localScaling", localScaling_);
	// Reconstruct the transformation
	isDirty_ = true;
	ReconstructTransformation();
}

// Private Member Functions //
void Junior::Transform::ReconstructTransformation()
{
	if (isDirty_)
	{
		localTransformation_ = Translation(localTranslation_) * Rotation(localRot_) * Scale(localScaling_);
		isDirty_ = false;
	}
}