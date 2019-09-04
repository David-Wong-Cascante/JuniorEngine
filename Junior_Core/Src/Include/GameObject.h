#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: GameObject.h
* Description: Define what a Game Object looks like
* Created: 28 Apr 2018
* Last Modified: 18 Jul 2019
*/

// Includes //
#include <vector>					// Vector
#include <typeinfo>					// Type Info
#include "Serializable.h"			// Serializable

namespace Junior
{
	// Forward Declarations //
	class GameObject;
	class MemoryManager;
	class ComponentContainer;
	class Parser;
	struct RenderJob;

	class GameObject : public Serializable
	{
	private:
		// Private Class Variables //
		// The name of the object
		std::string name_;
		// The parent of this game bject
		GameObject* parent_;
		// If this game object is destroyed or not
		bool destroyed_;
		// Whether this game object is being used as an archetype
		bool isArchetype_;
		// The components of this game object
		std::vector<ComponentContainer*> components_;
		// The children of this game object
		std::vector<GameObject*> children_;
	public:
		// Public Member Functions //
		// Constructor
		// Params:
		//	name: The name of the game object
		//	isArchetype: Whether the object is an archetype or not
		//	This field is used to determine whether rendering links should be used or not
		GameObject(const std::string& name = "Object", bool isArchetype = false);
		// Copy Constructor - Copies the game object and its components
		// Params:
		//	other: The other game object we are copying from
		GameObject(const GameObject& other);
		// Destructor destroys the game object
		~GameObject();
		// Initalizes all of the components inside of it
		void Initialize();
		// Updates the components of the game object
		// Params:
		//	ms: The delta time between frames
		void Update(double ms);
		// Updates the components of the game object at constant dt
		// Params:
		//	ms: The delta time between frames
		void FixedUpdate(double ms);
		// Shutsdown the game object
		void Shutdown();
		// Cleans the game object and its components
		// Params:
		//	manager: The memory manager used to create the game object
		void Unload();
		// Adds a child game object to this one
		// Params:
		// child: Thie child game object
		void AddChild(GameObject* child);
		// Adds a component to this instance of GameObject
		// Params: 
		//	component: The component to be added
		void AddComponent(ComponentContainer* component);
		// Removes a component from this GameObject
		// Params:
		//	type: The component's type
		void RemoveComponent(const std::string& name);
		// Serializes the game object
		// Params:
		//	parser: The parser to serialize to
		// Throws: ParserException
		void Serialize(Parser& parser) const override;
		// Deserializes the game object
		// Params:
		//	parser: The parser to deserialize to
		// Throws: ParserException
		void Deserialize(Parser& parser) override;
		// Sets the name of the game object
		// Params:
		//	name: The new name of the game object
		void SetName(const std::string& name);
		// Returns: The name of the game object
		std::string GetName() const;
		// Returns: The parent of this game object
		GameObject* GetParent() const;
		// Returns: The children in a list
		const std::vector<GameObject*>& GetChildren() const;
		// Gives a pointer to a selected component
		// Params:
		//	type: The type of component we are looking for
		// Returns: The first component in the list of components with the desired component type
		ComponentContainer* GetComponent(const std::string& name) const;
		// Gives a pointer to a selected component
		template <class T>
		T* GetComponent()
		{
			// Search through each component to see if we found a component with the correct type
			auto end = components_.end();
			for (auto begin = components_.begin(); begin < end; ++begin)
			{
				if (typeid(**begin) == typeid(T) || dynamic_cast<T*>(*begin))
				{
					return static_cast<T*>(*begin);
				}
			}

			return nullptr;
		}
		// Destroys the game object
		void Destroy();
		// Returns: Whether the object is destroyed
		bool IsDestroyed();
		// Returns: Whether this object is an archetype or not
		bool IsArchetype();
	};
}