/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* Date Created: 1-May-2018
* Last Modified: 11-Dec-2018
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

// Public Member Functions //

Junior::Transform::Transform() 
	: localRot_(0.0f), localTranslation_({0, 0, 0, 1}), localScaling_({1, 1, 1, 0})
{
	this->type_ = ComponentType::TRANSFORM;
};

void Junior::Transform::Initialize()
{
	this->updateable_ = true;
	job_ = owner_->GetRenderJob();
	ReconstructTransformation();
}

void Junior::Transform::Update(double ms)
{
	// Reconstruct the matrix if necessary
	ReconstructTransformation();
	if (job_)
	{
		// Set the render jobs matrix pointer
		job_->transformation_ = GetGlobalTransformation();
	}
}

void Junior::Transform::Clean(MemoryManager* manager)
{
}

void Junior::Transform::SetLocalTranslation(const Vec3& other)
{
	if (other.x_ == localTranslation_.x_ && other.y_ == localTranslation_.y_ && other.z_ == localTranslation_.z_)
		return;

	isDirty = true;
	localTranslation_ = other;
}

void Junior::Transform::SetLocalScaling(const Vec3& other)
{
	if (other.x_ == localScaling_.x_ && other.y_ == localScaling_.y_ && other.z_ == localScaling_.z_)
		return;

	isDirty = true;
	localScaling_ = other;
}

void Junior::Transform::SetLocalRotation(const float other)
{
	if (other == localRot_)
		return;

	isDirty = true;
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
			Transform* parentTransform = static_cast<Transform*>(parent->GetComponent(type_));
			if (parentTransform)
			{
				globalTransformation = parentTransform->GetGlobalTransformation();
			}
		}
	}
	return globalTransformation * localTransformation_;
}

// Private Member Functions //
void Junior::Transform::ReconstructTransformation()
{
	if (isDirty)
	{
		localTransformation_ = Translation(localTranslation_) * Rotation(localRot_) * Scale(localScaling_);
		isDirty = false;
	}
}