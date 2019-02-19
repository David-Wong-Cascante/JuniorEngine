#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: GameObject.h
* Description: Define the Game Object functionality to get components, get its name, update, etc...
* Created: 1-May-2018
* Last Modified: 18-Feb-2019
*/

// Includes //
#include "GameObject.h"

#include "RenderJob.h"			// Render Job
#include "Component.h"			// Component
#include "Graphics.h"			// Graphics
#include "MemoryManager.h"		// Memory Manager

// Public Member Functions //

Junior::GameObject::GameObject(const char* name, bool rendered)
	: name_(name), components_(), children_(), parent_(nullptr), destroyed(false), renderJob_(nullptr)
{
	Graphics& graphics = Graphics::GetInstance();
	if(rendered)
		renderJob_ = graphics.GetNewRenderJob();
}

Junior::GameObject::~GameObject()
{
	Destroy();
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

	if (renderJob_)
	{
		Graphics& graphics = Graphics::GetInstance();
		graphics.RemoveRenderJob(renderJob_);
		delete renderJob_;
		renderJob_ = nullptr;
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

// Gets the object's children
const std::vector<Junior::GameObject*>& Junior::GameObject::GetChildren() const
{
	return children_;
}

Junior::RenderJob* Junior::GameObject::GetRenderJob() const
{
	return renderJob_;
}

// Add the component to the game object
void Junior::GameObject::AddComponent(Component* component)
{
	component->SetOwner(this);
	component->Initialize();
	components_.push_back(component);
}

// Removes the component from the game object
void Junior::GameObject::RemoveComponent(const std::string& type)
{
	// Iterate through the list of components until we find the component we are looking for
	for (unsigned i = 0; i < components_.size(); ++i)
	{
		if (components_[i]->GetTypeName() == type)
		{	
			// Remove the first component with the type
			components_.erase(components_.begin() + i);
			return;
		}
	}
}

// Get the first component it finds based on on the component's id
Junior::Component * Junior::GameObject::GetComponent(const std::string& type) const
{
	for (Component* component : components_)
	{
		if (component->GetTypeName() == type)
		{
			return component;
		}
	}
	return nullptr;
}

void Junior::GameObject::Destroy()
{
	destroyed = true;

	// Destroy all the children objects as well
	for (GameObject* child : children_)
	{
		child->Destroy();
	}
}

bool Junior::GameObject::IsDestroyed()
{
	return destroyed;
}