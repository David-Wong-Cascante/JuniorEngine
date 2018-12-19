#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: GameObject.h
* Description: Define the Game Object functionality to get components, get its name, update, etc...
* Created: 1-May-2018
* Last Modified: 11-Dec-2018
*/

// Includes //
#include "GameObject.h"

#include "RenderJob.h"			// Render Job
#include "MemoryManager.h"		// Memory Manager
#include "Component.h"			// Component

// Public Member Functions //

Junior::GameObject::GameObject(const char* name)
	: name_(name), components_(), children_(), renderJobs_(), parent_(nullptr), destroyed(false)
{
}

void Junior::GameObject::Initialize()
{
	for (Component* component : components_)
	{
		component->Initialize();
	}
}

// Update all the objects, and ignore all the objects that are not marked for updating
void Junior::GameObject::Update(double ms)
{
	if (components_.size() > 0)
	{
		for (Component* component : components_)
		{
			if (component->IsUpdateable())
			{
				component->Update(ms);
			}
		}
	}

	// TODO: Look for any children that are marked for destruction and get rid of the objects
}

void Junior::GameObject::AddChild(GameObject* child)
{
	child->parent_ = this;
	children_.push_back(child);
}

void Junior::GameObject::Clean(MemoryManager* manager)
{
	if (components_.size() > 0)
	{
		for (Component* component : components_)
		{
			// If the component exists, then clean it up and delete it
			if (component)
			{
				component->Clean(manager);
				//manager->DeAllocate(component);
				delete component;
				component = 0;
			}
		}
	}
}

// Get the objects's name
const char* Junior::GameObject::GetName() const
{
	return name_;
}

// Get's the object's parent
Junior::GameObject* Junior::GameObject::GetParent() const
{
	return parent_;
}

// Add the component to the game object
void Junior::GameObject::AddComponent(Component* component)
{
	component->SetOwner(this);
	components_.push_back(component);
}

// Get the first component it finds based on on the component's id
Junior::Component * Junior::GameObject::GetComponent(ComponentType type)
{
	for (Component* component : components_)
	{
		if (component->GetType() == type)
		{
			return component;
		}
	}
	return nullptr;
}

void Junior::GameObject::Destroy()
{
	destroyed = true;
}

bool Junior::GameObject::IsDestroyed()
{
	return destroyed;
}