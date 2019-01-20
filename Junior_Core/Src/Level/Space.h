#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Space.h
* Description: The class where all levels reside
* Created: 18-Dec-2018
* Last Modified: 18-Dec-2018
*/

#include "GameSystem.h"

namespace Junior
{
	// Forward Declarations
	class Level;

	class Space : public GameSystem
	{
	private:
		// Private Variables
		Level* currentLevel_;
		Level* nextLevel_;

		// Helper function to move from level to level
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
		// Change the level inside the space
		// Params:
		//	level: The next level we want to load
		void NextLevel(Level* level);
		// Restarts the current level
		void RestartLevel();
	};
}