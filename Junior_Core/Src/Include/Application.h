#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Application.h
* Description: Encapsulates all of the engines components under one class
* Created: 27-Mar-2019
* Last Modified: 18 Apr 2019
*/

// Includes
#include "GameSystem.h"			// Game System
#include "MemoryManager.h"		// Memory Manager
#include <vector>				// vector

namespace Junior
{
	// Forward Declaration
	class Space;
	class Level;
	class GameSystem;

	class Application
	{
	private:
		// Private Member Variables

		// The current space our world is in
		Space* currentSpace_;
		// The current level
		Level* currentLevel_;
		// The application's memory manager
		MemoryManager manager;
		// All the game systems
		std::vector<GameSystem*> gameSystems_;
		// Private Member Functions

		// Updates the application
		void Update();
	public:
		// Public Member Functions 

		// Constructor
		// Params:
		//	level: The level we are loading in
		Application(Level* level);
		// Destructor
		~Application();
		// Loads the application
		bool Load();
		// Initializes the application
		bool Initialize();
		// Starts running the app
		void Start();
		// Shutsdown the application
		void Shutdown();
		// Unloads the application
		void Unload();

		template <class T>
		// Adds a game system to the application
		void AddGameSystem()
		{
			gameSystems_.push_back(&T::GetInstance());
		}
	};
}