#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: ComponentContainer.cpp
* Description: Wraps around a component
* Created: 8-Apr-2019
* Last Modified: 8-Apr-2019
*/

// Includes
#include "ComponentContainer.h"		// Component Container
#include "Component.h"				// Component

// Protected Member Functions

Junior::ComponentContainer::ComponentContainer()
{

}

// Public Member Functions

Junior::ComponentContainer::~ComponentContainer()
{
}

void Junior::ComponentContainer::SetOwner(GameObject* cog)
{
	owner_ = cog;
}

const std::string Junior::ComponentContainer::GetTypeName() const
{
	return name_;
}

bool Junior::ComponentContainer::IsUpdateable() const
{
	return updateable_;
}