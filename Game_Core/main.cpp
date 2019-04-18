/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: main.cpp
* Description: Starts up the program
* Created: 11 Dec 2018
* Last Modified: 18 Apr 2019
*/

// Includes
#include "Application.h"			// Application
// Starting level
#include "TestLevel.h"				// Test Level

int main(void)
{
	// Initialize the application
	Junior::Application app(new Junior::TestLevel);

	if (!app.Load())
		return -1;
	if (!app.Initialize())
		return -1;

	app.Start();

	return 0;
}