/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: main.cpp
* Description: Starts up the program
* Created: 11-Dec-2018
* Last Modified: 18-Dec-2018
*/

#include <iostream>							// IO Stream
#include <string>							// String
#include <math.h>							// Math

#include "MemoryLeakGuard.h"				// Memory Leak Guard
#include "Graphics.h"						// Graphics
#include "Time.h"							// Time
#include "Input.h"							// Input
#include "MemoryManager.h"					// Memory Manager
#include "GameObjectManager.h"				// Game Object Manager
#include "OpenGLBundle.h"					// OpenGL

#include "Space.h"							// Space
#include "TestLevel.h"						// Test Level

int main(void)
{
	// Set up the memory leak guard
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif
	// Initialize the memory manager for everything else in the game engine
	Junior::MemoryManager manager;
	// Create the Graphics class
	Junior::Graphics& g = Junior::Graphics::GetInstance();

	// Load the Graphics class
	if (!g.Load())
	{
		return -1;
	}
	// Initialize the Graphics class
	if (!g.Initialize())
	{
		return -1;
	}

	// Load the space
	Junior::Space* space = new Junior::Space("CurrentSpace");
	space->NextLevel(new Junior::TestLevel);

	// Create the game loop
	while (!g.WindowRequestClosed())
	{
		// Update all of the time functions
		Junior::Time::GetInstance().Update(0);
		// Quit the game loop if the user presses escape
		if (Junior::Input::GetKeyState(GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			break;
		}

		// Update the graphics
		space->Update(Junior::Time::GetInstance().GetDeltaTime());
		g.Render();
		g.PollWindow();
	}

	Junior::GameObjectManager::GetInstance().CleanUp(&manager);
	//
	//manager.DeAllocate(cog);
	//manager.DeAllocate(cog2);

	space->Shutdown();
	space->Unload();
	g.Shutdown();
	g.Unload();

	delete space;
	//std::cin.get();

	return 0;
}