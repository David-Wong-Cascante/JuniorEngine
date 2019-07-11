/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: Physics.cpp
 * Description: Takes care of any physical motion
 * Created: 7 July 2019
 * Last Modified: 7 July 2019
*/

// Includes
#include "Physics.h"			// Physics
#include "GameObject.h"			// Game Object
#include "Transform.h"			// Transform

// Public Member Functions

Junior::Physics::Physics(float mass)
	: inverseMass_(1.0f / mass), velocity_(0.0f, 0.0f, 0.0f), angularVelocity_(0.0f), acceleration_(0.0f, 0.0f, 0.0f),
	  prevPosition_(0.0f, 0.0f, 0.0f), transform_(nullptr)
{
}

Junior::Physics::Physics(const Physics& other)
	: inverseMass_(other.inverseMass_), velocity_(other.velocity_), angularVelocity_(other.angularVelocity_), acceleration_(other.acceleration_),
	  prevPosition_(other.prevPosition_), transform_(nullptr)
{
}

void Junior::Physics::Initialize()
{
	// Get the object's transform
	transform_ = owner_->GetComponent<Transform>();
}

void Junior::Physics::Update(double dt)
{
	// First, save the object's previous position
	prevPosition_ = transform_->GetLocalTranslation();
	Vec3 position = prevPosition_;
	// Then, perform physics operations on the object
	velocity_ += acceleration_ * static_cast<float>(dt);
	acceleration_ = Vec3(0.0f, 0.0f, 0.0f);
	position += velocity_ * static_cast<float>(dt);
	transform_->SetLocalTranslation(position);
	// Rotate the object accordingly
	float currRotation = transform_->GetLocalRotation();
	currRotation += angularVelocity_ * static_cast<float>(dt);
	transform_->SetLocalRotation(currRotation);
}

void Junior::Physics::Unload()
{
}

void Junior::Physics::Serialize(Parser& parser) const
{
	parser.WriteVariable("mass", 1.0f / inverseMass_);
}

void Junior::Physics::Deserialize(Parser& parser)
{
	float mass;
	parser.ReadVariable("mass", mass);
	// Set the inverse mass, I know it's weird
	SetMass(mass);
}

void Junior::Physics::SetMass(float mass)
{
	inverseMass_ = 1.0f / mass;
}

void Junior::Physics::SetVelocity(const Vec3& other)
{
	velocity_ = other;
}

void Junior::Physics::SetAngularVelocity(float angular)
{
	angularVelocity_ = angular;
}

void Junior::Physics::AddForce(const Vec3& force)
{
	acceleration_ = force * inverseMass_;
}

const Junior::Vec3& Junior::Physics::GetVelocity() const
{
	return velocity_;
}

float Junior::Physics::GetAngularVelocity() const
{
	return angularVelocity_;
}

const Junior::Vec3& Junior::Physics::GetPrevPosition() const
{
	return prevPosition_;
}