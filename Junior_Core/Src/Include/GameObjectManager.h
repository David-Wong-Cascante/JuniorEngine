#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: GameObjectManager.h
* Description: Takes care to initialize, update, and clean up all of the objects
* Created: 11 Dec 2018
* Last Modified: 10 Sep 2019
*/

// Includes //
#include <vector>				// Vector
#include <string>				// String
#include "GameSystem.h"			// Game System

namespace Junior
{
	// Forward Declarations //
	class GameObject;
	class MemoryManager;

	class GameObjectManager : public GameSystem
	{
	private:

		// Private Member Constants

		// The fixed delta time we are targetting
		const double fixedDtTarget_;

		// Private Member Variables

		// The fixed delta time accumulator that runs fixed update
		double fixedDtAccumulator_;
		// The game objects
		std::vector<GameObject*> gameObjects_;
		// The archetypes for these objects
		std::vector<GameObject*> archetypes_;
		// The destroyed game objects
		std::vector<GameObject*> destroyedObjects_;

		// Private Member Functions

		// Default Constructor
		GameObjectManager();
	public:
		// Loads the game object manager
		// Returns: Whether the game object manager succeded in loading
		bool Load() override;
		// Initializes the game object manager
		// Returns: Whether the game object manager succeded in initializing
		bool Initialize() override;
		// Renders the game object manager
		void Render() override;
		// Updates the game object manager, and updates all of the other objects inside
		// Params:
		// dt: The delta time between frames
		void Update(double dt) override;
		// Shutsdown the game object manager
		void Shutdown() override;
		// Cleans up all of the objects and deletes them
		// Params:
		//	manager: The memory manager used to create all of these objects
		void Unload() override;
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
		// Returns: All of the objects in the manager
		const std::vector<GameObject*>& GetAllObjects() const;

		// Gets the classes' singleton
		// Returns: The classes' singleton
		static GameObjectManager& GetInstance();
	};
}