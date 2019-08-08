/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: EventManager.cpp
* Description: Dispatches events to objects throughout the game
* Created: 7 Aug 2019
* Last Modified: 7 Aug 2019
*/

// Includes
#include "EventManager.h"			// Event Manager
#include "Event.h"					// Basic Event

// Private Member Functions

Junior::EventManager::EventManager()
	: GameSystem("EventManager")
{
}

Junior::CallbackDispatcher& Junior::EventManager::CreateEventMapSlot(const std::string& name)
{
}

void Junior::EventManager::DispatchEvent(Junior::Event* event)
{
}

// Public Static Functions

Junior::EventManager& Junior::EventManager::GetInstance() const
{
	static EventManager manager;
	return manager;
}

// Public Member Functions

bool Junior::EventManager::Load()
{
}

bool Junior::EventManager::Initialize()
{
}

void Junior::EventManager::Update(double dt)
{
}

void Junior::EventManager::Render()
{
}

void Junior::EventManager::Shutdown()
{
}

void Junior::EventManager::Unload()
{
}

void Junior::EventManager::Subscribe(const std::string& name, void* object, Junior::EventCallback callback)
{
}

void Junior::EventManager::Unsubscribe(const std::string& name, const void* object, Junior::EventCallback callback)
{
}

void Junior::EventManager::SendEvent(const Event* event)
{
}

void Junior::EventManager::SetEventProcessingCap(unsigned processingCap)
{
	eventProcessingCap_ = processingCap;
}

unsigned Junior::EventManager::GetEventProcessingCap() const
{
	return eventProcessingCap_;
}