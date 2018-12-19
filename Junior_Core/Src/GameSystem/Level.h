/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Level.h
* Description: Defines what a level is, with game objects and everything
* Created: 18-Dec-2018
* Last Modified: 18-Dec-2018
*/

// Includes
#include "GameSystem.h"			// Game System

namespace Junior
{
	class Level : public GameSystem
	{
	public:
		// Constructor
		// Params:
		//	name: The name of the level
		Level(const char* name);
		// Loads the level
		bool virtual Load() override;
		// Initializes the level
		bool Initialize() override;
		// Updates the level
		void Update(double dt) override;
		// Renders the level
		void Render() override;
		// Shuts down the level
		void Shutdown() override;

	//private:
	};
}