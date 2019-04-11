/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Application.cpp
* Description: Encapsulates all of the engines components under one class
* Created: 27-Mar-2019
* Last Modified: 27-Mar-2019
*/

// Includes
#include "Application.h"

#include "Graphics.h"				// Graphics
#include "Debug.h"					// Debug
#include "Input.h"					// Input
#include "GameObjectManager.h"		// Game Object Manager
#include "Time.h"					// Time

#include "Space.h"					// Space
#include "Level.h"					// Level
#include "MemoryLeakGuard.h"		// Memory Leak Guard

#include "Parser.h"
#include "LinearMath.h"

// Public Member Functions

Junior::Application::Application(Junior::Level* startingLevel)
	: currentLevel_(startingLevel), manager()
{
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

	if (!Graphics::GetInstance().Load())
	{
		debug.Print<std::string>(debug.GetDebugLevelName(Junior::DebugLevel::ERROR));
		debug.PrintLn<std::string>("Graphics failed to load up!");
		return false;
	}

	if (!Input::GetInstance().Load())
	{
		debug.Print<std::string>(debug.GetDebugLevelName(Junior::DebugLevel::ERROR));
		debug.PrintLn<std::string>("Input failed to load up!");
		return false;
	}

	return true;
}

bool Junior::Application::Initialize()
{
	// Initialize the input, time and graphics
	Graphics::GetInstance().Initialize();
	Input::GetInstance().Initialize();
	Time::GetInstance().Initialize();

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
	Graphics::GetInstance().Update(Junior::Time::GetInstance().GetDeltaTime());
	Graphics::GetInstance().Render();
	Graphics::GetInstance().PollWindow();
}

void Junior::Application::Shutdown()
{
	currentSpace_->Shutdown();
	Input::GetInstance().Shutdown();
	Graphics::GetInstance().Shutdown();
	currentSpace_->Shutdown();
}

void Junior::Application::Unload()
{
	GameObjectManager::GetInstance().CleanUp(&manager);
	Input::GetInstance().Unload();
	Graphics::GetInstance().Unload();
	currentSpace_->Unload();
	delete currentSpace_;
}