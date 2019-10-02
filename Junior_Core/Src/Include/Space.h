#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Space.h
* Description: The class where all levels reside
* Created: 18 Dec 2018
* Last Modified: 2 Oct 2019
*/

#include "GameSystem.h"
#include "GameObjectManager.h"			// Game Object Manager

namespace Junior
{
	// Forward Declarations
	class Level;

	class Space : public GameSystem
	{
	private:
		// Private Variables
		// Whether this space is marked for a restart
		bool markedForRestart_;
		// The current level that is playing
		Level* currentLevel_;
		// The previous level
		Level* nextLevel_;
		// The object manager for this space
		GameObjectManager manager_;

		// Moves from one level to another
		void MoveLevels();
	public:
		// Constructor
		Space(const char* name);
		// Loads the assets for the space
		// Returns: Whether the Space managed to load the assets
		bool Load() override;
		// Initializes the space
		// Returns: Whether the Space managed to initialize
		bool Initialize() override;
		// Updates the component
		// Params:
		//	dt: The time between frames
		void Update(double dt) override;
		// Renders the space (should debug draw be a feature in the future)
		void Render() override;
		// Shuts down the space
		void Shutdown() override;
		// Unloads the space
		void Unload() override;
		// Gets the object manager for this space
		// Returns: The game object manager for this space
		GameObjectManager* GetObjectManager();
		// Change the level inside the space
		// Params:
		//	level: The next level we want to load
		void NextLevel(Level* level);
		// Restarts the current level
		void RestartLevel();
	};
}