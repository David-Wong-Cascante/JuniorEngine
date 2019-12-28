/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Application.cpp
* Description: Encapsulates all of the engines components under one class
* Created: 27 Mar 2019
* Last Modified: 10 Sep 2019
*/

// Includes
#include "Application.h"

#include "Debug.h"					// Debug

#include "GameSystem.h"				// Game System
#include "Graphics.h"				// Graphics
#include "Input.h"					// Input
#include "Time.h"					// Time
#include "ResourceManager.h"		// Resource Manager
#include "EventManager.h"			// Event Manager
#include "Event.h"					// Event

#include "Space.h"					// Space
#include "Level.h"					// Level
#include "MemoryLeakGuard.h"		// Memory Leak Guard
#include "LinearMath.h"				// Linear Math Help

// Defines
#define NUM_DEFAULT_SYSTEMS 4

// Global Function Declaration

// Quits the application
// Params:
//	object: The application we are quitting
//	event: The event that triggered the quit
void QuitViaEvent(void* object, const Junior::Event* event);


// Public Member Functions

Junior::Application::Application(Junior::Level* startingLevel)
	: currentLevel_(startingLevel), gameSystems_(), quit_(false)
{
	// Pregister all the game systems need in this application
	gameSystems_.reserve(NUM_DEFAULT_SYSTEMS);
	// Time always goes first because it doesn't matter what dt it updates to while
	// the rest of the systems do care what the dt is
	AddGameSystem<Time>();
	AddGameSystem<Input>();
	AddGameSystem<ResourceManager>();
	AddGameSystem<EventManager>();
	AddGameSystem<Graphics>();
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

	// Subscribe to a event
	EventManager& eventManager = EventManager::GetInstance();
	eventManager.Subscribe(KeyEvent::KeyEventName, this, QuitViaEvent);
	eventManager.Subscribe(WindowQuitEvent::WindowQuitEventName, this, QuitViaEvent);
	return true;
}

void Junior::Application::Start()
{
	while (!quit_)
	{
		Update();
	}
}

void Junior::Application::Update()
{
	// Update all of the game systems
	for (auto begin = gameSystems_.begin(); begin != gameSystems_.end(); ++begin)
	{
		(*begin)->Update(Time::GetInstance().GetDeltaTime());
	}

	// Then, update the space
	currentSpace_->Update(Time::GetInstance().GetDeltaTime());

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

	// Unsubscribe to quit via event
	EventManager& eventManager = EventManager::GetInstance();
	eventManager.Unsubscribe(KeyEvent::KeyEventName, this, QuitViaEvent);
	eventManager.Unsubscribe(WindowQuitEvent::WindowQuitEventName, this, QuitViaEvent);
}

void Junior::Application::Unload()
{
	currentSpace_->Unload();
	delete currentSpace_;

	// Unload all of the game systems
	for (auto begin = gameSystems_.begin(); begin != gameSystems_.end(); ++begin)
	{
		(*begin)->Unload();
	}
}

void Junior::Application::Quit()
{
	quit_ = true;
}

void QuitViaEvent(void* object, const Junior::Event* event)
{
	// Get the object as the application
	Junior::Application* app = reinterpret_cast<Junior::Application*>(object);
	if (event->name_ == Junior::KeyEvent::KeyEventName)
	{
		// The user pressed a button, check if it is escape, then quit
		const Junior::KeyEvent* keyEvent = reinterpret_cast<const Junior::KeyEvent*>(event);
		if (keyEvent->key_ == GLFW_KEY_ESCAPE && keyEvent->action_ == GLFW_PRESS)
		{
			if (app)
			{
				app->Quit();
			}
		}
	}
	else if (event->name_ == Junior::WindowQuitEvent::WindowQuitEventName)
	{
		if (app)
		{
			app->Quit();
		}
	}
}