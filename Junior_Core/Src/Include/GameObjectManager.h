#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: GameObjectManager.h
* Description: Takes care to initialize, update, and clean up all of the objects
* Created: 11 Dec 2018
* Last Modified: 18 Apr 2019
*/

// Includes //
#include <vector>

namespace Junior
{
	// Forward Declarations //
	class GameObject;
	class MemoryManager;

	class GameObjectManager
	{
	private:
		// Private Member Variables //
		std::vector<GameObject*> gameObjects_;
		std::vector<GameObject*> destroyedObjects_;
		// Default Constructor
		GameObjectManager();
	public:
		// Public Member Functions //
		// Adds the game object to the manager and initializes it
		// Params:
		//	object: The object to initialize
		void AddObject(GameObject* const object);

		// Updates the game object manager, and updates all of the other objects inside
		// Params:
		//	manager: The memory manger used to create all of the objects
		void Update(MemoryManager* manager);

		// Cleans up all of the objects and deletes them
		// Params:
		//	manager: The memory manager used to create all of these objects
		void CleanUp(MemoryManager* manager);

		// Gets the classes' singleton
		// Returns: The classes' singleton
		static GameObjectManager& GetInstance();
	};
}