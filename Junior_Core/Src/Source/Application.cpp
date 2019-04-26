/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Application.cpp
* Description: Encapsulates all of the engines components under one class
* Created: 27 Mar 2019
* Last Modified: 19 Apr 2019
*/

// Includes
#include "Application.h"

#include "Debug.h"					// Debug

#include "GameSystem.h"				// Game System
#include "Graphics.h"				// Graphics
#include "Input.h"					// Input
#include "Time.h"					// Time
#include "ResourceManager.h"		// Resource Manager
#include "GameObjectManager.h"		// Game Object Manager

#include "Space.h"					// Space
#include "Level.h"					// Level
#include "MemoryLeakGuard.h"		// Memory Leak Guard
#include "LinearMath.h"				// Linear Math Help

// Defines
#define NUM_DEFAULT_SYSTEMS 4

// Public Member Functions

Junior::Application::Application(Junior::Level* startingLevel)
	: currentLevel_(startingLevel), manager(), gameSystems_()
{
	// Pregister all the game systems need in this application
	gameSystems_.reserve(NUM_DEFAULT_SYSTEMS);
	AddGameSystem<Graphics>();
	AddGameSystem<Time>();
	AddGameSystem<Input>();
	AddGameSystem<ResourceManager>();
}

Junior::Application::~Application()
{
	Shutdown();
	Unload();
}

bool Junior::Application::Load()
{
	// Set up the debug file output
	Debug& debug = Debug::GetInstance();
	debug.SetOutputFile("JuniorDebugInfo.txt");
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	debug.Print<std::string>(debug.GetDebugLevelName(Junior::DebugLevel::NOTIFICATION));
	debug.PrintLn<std::string>("Debug Memory Management Enabled");
#endif

	// Load all of the game systems
	for (auto begin = gameSystems_.begin(); begin < gameSystems_.end(); ++begin)
	{
		if (!(*begin)->Load())
		{
			debug.Print(debug.GetDebugLevelName(Junior::DebugLevel::ERROR));
			debug.PrintLn(std::string((*begin)->GetName()) + " failed to load!");
		}
	}

	return true;
}

bool Junior::Application::Initialize()
{
	// Initialize the game systems
	Debug& debug = Debug::GetInstance();
	for (auto begin = gameSystems_.begin(); begin < gameSystems_.end(); ++begin)
	{
		if (!(*begin)->Initialize())
		{
			debug.Print(debug.GetDebugLevelName(Junior::DebugLevel::ERROR));
			debug.PrintLn(std::string((*begin)->GetName()) + " failed to initialize!");
		}
	}

	// Load the space with the level
	currentSpace_ = new Space("CurrentSpace");
	currentSpace_->NextLevel(currentLevel_);
	return true;
}

void Junior::Application::Start()
{
	while (!Graphics::GetInstance().WindowRequestClosed())
	{
		Junior::Time::GetInstance().Update(0);
		if (Input::GetInstance().GetKeyState(GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			break;
		}

		Update();
	}
}

void Junior::Application::Update()
{
	currentSpace_->Update(Junior::Time::GetInstance().GetDeltaTime());
	// Update all of the game systems
	for (auto begin = gameSystems_.begin(); begin != gameSystems_.end(); ++begin)
	{
		(*begin)->Update(Time::GetInstance().GetDeltaTime());
	}

	// Render all of the game systems
	for (auto begin = gameSystems_.begin(); begin != gameSystems_.end(); ++begin)
	{
		(*begin)->Render();
	}
	
	Graphics::GetInstance().PollWindow();
}

void Junior::Application::Shutdown()
{
	currentSpace_->Shutdown();
	// Shut down all the systems
	// Render all of the game systems
	for (auto begin = gameSystems_.begin(); begin != gameSystems_.end(); ++begin)
	{
		(*begin)->Shutdown();
	}
}

void Junior::Application::Unload()
{
	GameObjectManager::GetInstance().CleanUp(&manager);
	currentSpace_->Unload();
	delete currentSpace_;

	// Unload all of the game systems
	for (auto begin = gameSystems_.begin(); begin != gameSystems_.end(); ++begin)
	{
		(*begin)->Unload();
	}
}