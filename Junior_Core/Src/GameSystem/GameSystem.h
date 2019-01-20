#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: GameSystem.h
* Description: Defines a general manner to organize all the systems
* Created: 18-Dec-2018
* Last Modified: 18-Dec-2018
*/

namespace Junior
{
	class GameSystem
	{
	private:
		// Private Variables
		const char* name_;
	protected:
		// Protected Member Functions
		// Constructor
		// Params:
		//	name: The name of the system we are creating
		GameSystem(const char* name);
	public:
		// Loads assets in the system
		// Returns: Whether the function was successful in loading the assets
		bool virtual Load() = 0;
		// Initializes the game system
		// Returns: Whether the function succeded in initializing or not
		bool virtual Initialize() = 0;
		// Updates the system
		// Params:
		//	dt: The time in between frames
		void virtual Update(double dt) = 0;
		// Renders the system, whether it is debug info or an actual render
		void virtual Render() = 0;
		// Shuts down the game system
		void virtual Shutdown() = 0;
		// Unloads the assets in the system
		void virtual Unload() = 0;
		// Returns: The name of the system
		const char* GetName() const;
	};

	// Global function that tests for GameSystem function results, and gives an error when the function failed
	// Params:
	//	result: Whether the function succeded or not
	//	errorMessage: The error message when the function didn't succeed
	void GameSystemAssert(bool result, const char* errorMessage);
}