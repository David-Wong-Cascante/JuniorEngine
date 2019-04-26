/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Level.h
* Description: Defines what a level is, with game objects and everything
* Created: 18 Dec 2018
* Last Modified: 26 Dec 2018
*/

// Includes
#include "GameSystem.h"			// Game System
#include "Serializable.h"		// Serializable

namespace Junior
{
	class Level : public GameSystem, public Serializable
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
		// Unloads the level
		void Unload() override;
		// Saves this level to a file
		// Params:
		//	parser: The parser to save the file
		void Serialize(Parser& parser) const override;
		// Loads a level from the file
		// Params:
		//	parser: The parser that is loading the file
		void Deserialize(Parser& parser) override;
};
}