/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Component.h
* Description: Define a couple of helper functions that help objects outside the classes inheriting Component
* Created: 1-May-2018
* Last Modified: 13-Feb-2019
*/

// Includes //
#include "Component.h"
#include "Graphics.h"			// Graphics

// Public Member Functions

Junior::Component::Component(bool updatable)
	: owner_(nullptr), updateable_(updatable), type_(ComponentType::NONE)
{
}

Junior::Component::~Component()
{

}

void Junior::Component::SetOwner(GameObject* cog)
{
	this->owner_ = cog;
}

const Junior::ComponentType Junior::Component::GetType() const
{
	return type_;
}

bool Junior::Component::IsUpdateable() const
{
	return updateable_;
}