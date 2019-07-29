/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: main.cpp
* Description: Starts up the program
* Created: 11 Dec 2018
* Last Modified: 28 Jul 2019
*/

// Includes
#include <Application.h>			// Application
#include <GameObjectFactory.h>		// Game Object Factory

// Custom Components
#include "PlayerController.h"		// Player Controller

// Starting level
#include "TestLevel.h"				// Test Level

int main(void)
{
	// Initialize the application
	Junior::Application app(new JuniorGame::TestLevel);
	Junior::GameObjectFactory& factory = Junior::GameObjectFactory::GetInstance();

	// Register extra components
	factory.RegisterComponent<JuniorGame::PlayerController>();

	if (!app.Load())
		return -1;
	if (!app.Initialize())
		return -1;

	app.Start();

	return 0;
}