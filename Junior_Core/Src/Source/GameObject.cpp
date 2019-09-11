#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: GameObject.h
* Description: Define the Game Object functionality to get components, get its name, update, etc...
* Created: 1 May 2018
* Last Modified: 10 Sep 2019
*/

// Includes //
#include "GameObject.h"

#include "RenderJob.h"			// Render Job
#include "Component.h"			// Component
#include "Graphics.h"			// Graphics
#include "GameObjectFactory.h"	// Game Object Factory
#include "Debug.h"				// Debug

// Public Member Functions //

Junior::GameObject::GameObject(const std::string& name, bool isArchetype)
	: name_(name), components_(), children_(), parent_(nullptr), destroyed_(false), isArchetype_(isArchetype)
{
	Graphics& graphics = Graphics::GetInstance();
}

Junior::GameObject::GameObject(const GameObject& other)
	: name_(other.name_), parent_(other.parent_), destroyed_(false), isArchetype_(false)
{
	Graphics& graphics = Graphics::GetInstance();
	// Create a render job if the other did have one
	// Then copy its components
	for (auto componentsBegin = other.components_.cbegin(); componentsBegin != other.components_.cend(); ++componentsBegin)
	{
		ComponentContainer* container = (*componentsBegin)->Clone();
		container->SetOwner(this);
		components_.push_back(container);
	}
	// Then copy its children
	for (auto childrenBegin = other.children_.cbegin(); childrenBegin != other.children_.cend(); ++childrenBegin)
	{
		GameObject* other = new GameObject(**childrenBegin);
		children_.push_back(other);
	}
}

Junior::GameObject::~GameObject()
{
	Destroy();
}

void Junior::GameObject::Initialize()
{
	for (ComponentContainer* component : components_)
	{
		component->Initialize();
	}
}
void Junior::GameObject::Update(double ms)
{
	if (components_.size() > 0)
	{
		for (ComponentContainer* component : components_)
		{
			// Update all the objects, and ignore all the objects that are not marked for updating
			if (component->IsUpdateable())
			{
				component->Update(ms);
			}
		}
	}
}

void Junior::GameObject::FixedUpdate(double dt)
{
	if (components_.size() > 0)
	{
		for (ComponentContainer* component : components_)
		{
			if (component->IsUpdateable())
			{
				component->FixedUpdate(dt);
			}
		}
	}
}

void Junior::GameObject::AddChild(GameObject* child)
{
	child->parent_ = this;
	children_.push_back(child);
}

void Junior::GameObject::Shutdown()
{
	if (components_.size() > 0)
	{
		for (ComponentContainer* component : components_)
		{
			// If the component exists, then clean it up and delete it
			if (component)
			{
				component->Shutdown();
			}
		}
	}
}

void Junior::GameObject::Unload()
{
	if (components_.size() > 0)
	{
		for (ComponentContainer* component : components_)
		{
			// If the component exists, then clean it up and delete it
			if (component)
			{
				component->Unload();
				//manager->DeAllocate(component);
				delete component;
				component = 0;
			}
		}
	}
}

// Add the component to the game object
void Junior::GameObject::AddComponent(ComponentContainer* component)
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

void Junior::GameObject::Serialize(Parser& parser) const
{
	// Serialize the name of the component
	parser.WriteValue(name_);
	// Then serialize the rest of the component
	parser.StarScope();
	// Write the number of components
	parser.WriteVariable("numComponents", components_.size());
	for (unsigned i = 0; i < components_.size(); ++i)
	{
		// Serialize every individual game object component
		parser.WriteValue(components_[i]->GetTypeName());
		parser.StarScope();
		components_[i]->Serialize(parser);
		parser.EndScope();
	}
	parser.EndScope();
}

void Junior::GameObject::Deserialize(Parser& parser)
{
	// Then start deserializing the rest of the components
	parser.Skip("{");
	int numComponents;
	parser.ReadVariable("numComponents", numComponents);
	for(size_t i = 0; i < numComponents; ++i)
	{
		// Create new components and save them to the game object
		std::string nameOfComponent;
		// Get the name of the component
		parser.ReadValue(nameOfComponent);
		ComponentContainer* component = GameObjectFactory::GetInstance().CreateComponent(nameOfComponent);
		// If the component is legal, then we need to serialize and add it to the component
		if (component)
		{
			parser.Skip("{");
			// Then serialize the component
			component->Deserialize(parser);
			// Add the component
			AddComponent(component);
		}
		else
		{
			Debug& debug = Debug::GetInstance();
			debug.Print(debug.GetDebugLevelName(DebugLevel::WARNING));
			debug.Print("Did not recognize the component name \"");
			debug.Print(nameOfComponent);
			debug.PrintLn("\" during deserialization");
		}
		parser.Skip("}");
	}
	parser.Skip("}");
}

// Set the object's name
void Junior::GameObject::SetName(const std::string& name)
{
	name_ = name;
}

// Get the objects's name
std::string Junior::GameObject::GetName() const
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

// Get the first component it finds based on on the component's id
Junior::ComponentContainer * Junior::GameObject::GetComponent(const std::string& type) const
{
	for (ComponentContainer* component : components_)
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
	destroyed_ = true;

	// Destroy all the children objects as well
	for (GameObject* child : children_)
	{
		child->Destroy();
	}
}

bool Junior::GameObject::IsDestroyed()
{
	return destroyed_;
}

bool Junior::GameObject::IsArchetype()
{
	return isArchetype_;
}