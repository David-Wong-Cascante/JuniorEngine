#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: GameObjectManager.h
* Description: Takes care to initialize, update, and clean up all of the objects
* Created: 11 Dec 2018
* Last Modified: 27 Apr 2019
*/

// Includes //
#include <vector>
#include <string>

namespace Junior
{
	// Forward Declarations //
	class GameObject;
	class MemoryManager;

	class GameObjectManager
	{
	private:
		// Private Member Variables //
		// The game objects
		std::vector<GameObject*> gameObjects_;
		// The archetypes for these objects
		std::vector<GameObject*> archetypes_;
		// The destroyed game objects
		std::vector<GameObject*> destroyedObjects_;
		// Default Constructor
		GameObjectManager();
	public:
		// Public Member Functions
		// Adds the game object to the manager and initializes it
		// Params:
		//	object: The object to initialize
		void AddObject(GameObject* const object);
		// Adds an archetype to the manager
		// Params:
		//	archetype: The archetype we want to initialize
		void AddArchetype(GameObject* const archetype);
		// Finds an object by name
		// Params:
		//	name: The name of the object we are looking for
		// Returns: The object with the same name
		GameObject* FindByName(const std::string& name) const;
		// Creates an archetype by name
		// Params:
		//	name: The name of the object we want to create
		// Returns: A game object related to the archetype
		GameObject* CreateFromArchetype(const std::string& name) const;
		// Updates the game object manager, and updates all of the other objects inside
		// Params:
		//	manager: The memory manger used to create all of the objects
		void Update(MemoryManager* manager);
		// Cleans up all of the objects and deletes them
		// Params:
		//	manager: The memory manager used to create all of these objects
		void CleanUp(MemoryManager* manager);
		// Returns: All of the objects in the manager
		const std::vector<GameObject*>& GetAllObjects() const;

		// Gets the classes' singleton
		// Returns: The classes' singleton
		static GameObjectManager& GetInstance();
	};
}