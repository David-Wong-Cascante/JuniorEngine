#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: GameObject.h
* Description: Define what a Game Object looks like
* Created: 28-Apr-2018
* Last Modified: 11-Dec-2018
*/

// Includes //
#include <vector>

namespace Junior
{
	// Forward Declarations //
	class GameObject;
	class MemoryManager;
	class Component;
	struct RenderJob;
	
	enum ComponentType;
	class GameObject
	{
	private:
		// Private Class Variables //
		const char* name_;
		GameObject* parent_;
		bool destroyed;
		std::vector<RenderJob*> renderJobs_;
		std::vector<Component*> components_;
		std::vector<GameObject*> children_;
	public:
		// Public Member Functions //
		// Constructor
		// Params:
		//	name: The name of the game object
		GameObject(const char* name);
		// Initalizes all of the components inside of it
		void Initialize();
		// Updates the components of the game object
		// Params:
		//	ms: The delta time between frames
		void Update(double ms);
		// Cleans the game object and its components
		// Params:
		//	manager: The memory manager used to create the game object
		void Clean(MemoryManager* manager);
		// Adds a child game object to this one
		// Params:
		// child: Thie child game object
		void AddChild(GameObject* child);
		// Adds a component to this instance of GameObject
		// Params: 
		//	component: The component to be added
		void AddComponent(Component* component);

		// Returns: The name of the game object
		const char* GetName() const;
		// Returns: The parent of this game object
		GameObject* GetParent() const;

		// Gives a pointer to a selected component
		// Params:
		//	type: The type of component we are looking for
		// Returns: The first component in the list of components with the desired component type
		Component* GetComponent(ComponentType type);

		// Destroys the game object
		void Destroy();

		// Shows if the object is being destroye or not
		// Returns: Whether the object is destroyed
		bool IsDestroyed();
		
	};
}