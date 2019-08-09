/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: EventManager.cpp
* Description: Dispatches events to objects throughout the game
* Created: 7 Aug 2019
* Last Modified: 8 Aug 2019
*/

// Includes
#include "EventManager.h"			// Event Manager
#include "Event.h"					// Basic Event

// Private Member Functions

Junior::EventManager::EventManager()
	: GameSystem("EventManager"), eventProcessingCap_(-1)
{
}

Junior::CallbackDispatcher& Junior::EventManager::FindEventMapSlot(const std::string& name)
{
	// If the find don't find instance of this name in the map
	if (callbackMap_.find(name) == callbackMap_.cend())
	{
		// Creates a new map event slot
		CallbackDispatcher* callbackDispatcher = new CallbackDispatcher;
		// Map the dispatcher with the specified name if it didn't already exist
		callbackMap_[name] = callbackDispatcher;
	}

	// And return this callback dispatcher
	return *callbackMap_[name];
}

void Junior::EventManager::DispatchEvent(const Junior::Event* event)
{
	// Find a dispatcher with the event's name and then execute all of that dispatchers events
	std::unordered_map<std::string, CallbackDispatcher*>::iterator foundDispatcher = callbackMap_.find(event->name_);
	if (foundDispatcher != callbackMap_.cend())
	{
		// Execute all of the dispatcher events
		for (auto dispatcherPair = foundDispatcher->second->cbegin(); dispatcherPair != foundDispatcher->second->cend(); ++dispatcherPair)
		{
			EventCallback callbackFunc = dispatcherPair->first;
			// Then fire the current dispatcher for all of the objects it is linked to
			for (auto objectIter = dispatcherPair->second.cbegin(); objectIter != dispatcherPair->second.cend(); ++objectIter)
			{
				// Fire the event
				callbackFunc(*objectIter, event);
			}
		}
	}
}

// Public Static Functions

Junior::EventManager& Junior::EventManager::GetInstance()
{
	static EventManager manager;
	return manager;
}

// Public Member Functions

bool Junior::EventManager::Load()
{
	// Load the map of event dispatchers
	callbackMap_ = std::unordered_map<std::string, CallbackDispatcher*>();
	return true;
}

bool Junior::EventManager::Initialize()
{
	return true;
}

void Junior::EventManager::Update(double dt)
{
	// Process the left over events
	int leftOverEvents = eventProcessingCap_;
	// Process our events until we have none left or we have reached the cap
	while (leftOverEvents-- != 0)
	{
		// The iterator for the current event
		std::list <const Event*>::const_iterator eventIterator = unprocessedEvents_.cbegin();
		if (eventIterator != unprocessedEvents_.cend())
		{
			const Event* currentEvent = *unprocessedEvents_.cbegin();
			DispatchEvent(currentEvent);
			// Delete the event after we are done with it
			delete currentEvent;
			// Then pop the event off the list
			unprocessedEvents_.pop_front();
		}

		// Or we break out of the event processing loop if we have no events left
		if (unprocessedEvents_.size() == 0)
		{
			break;
		}
	}
}

void Junior::EventManager::Render()
{
}

void Junior::EventManager::Shutdown()
{
}

void Junior::EventManager::Unload()
{
	// Delete all of the dispatchers inside the map
	for (auto cbeginPair = callbackMap_.cbegin(); cbeginPair != callbackMap_.cend(); ++cbeginPair)
	{
		delete cbeginPair->second;
	}
	// Clear the map when we are done with it
	callbackMap_.clear();
	// Unload all the leftover events we still have
	for (auto event = unprocessedEvents_.cbegin(); event != unprocessedEvents_.cend(); ++event)
	{
		delete (*event);
	}
	unprocessedEvents_.clear();
}

void Junior::EventManager::Subscribe(const std::string& name, void* object, Junior::EventCallback callback)
{
	// Get the dispatcher
	CallbackDispatcher& foundDispatcher = FindEventMapSlot(name);
	// Find if the dispatcher has a spot for the callback
	CallbackDispatcher::iterator callbackIter = foundDispatcher.find(callback);
	// If the iterator exists then use that, if not then create a space for this EventCallback
	if (callbackIter == foundDispatcher.cend())
	{
		foundDispatcher[callback] = std::vector<void*>();
		callbackIter = foundDispatcher.find(callback);
	}

	// Add this object to the dispatcher
	callbackIter->second.push_back(object);
}

void Junior::EventManager::Unsubscribe(const std::string& name, const void* object, Junior::EventCallback callback)
{
	// Find the callback dispatcher first
	CallbackDispatcher& foundDispatcher = FindEventMapSlot(name);
	// Then, find the list tof objects using the callback as a key
	CallbackDispatcher::iterator callbackIter = foundDispatcher.find(callback);
	// If the callback exists, then check if the object is attached to this callback
	if (callbackIter != foundDispatcher.cend())
	{
		// Search for this object pointer
		for (auto cObjectBegin = callbackIter->second.cbegin(); cObjectBegin != callbackIter->second.cend(); ++cObjectBegin)
		{
			if (object == (*cObjectBegin))
			{
				callbackIter->second.erase(cObjectBegin);
				return;
			}
		}
	}
}

void Junior::EventManager::SendEvent(Event* event)
{
	// Send the event to the event list
	unprocessedEvents_.push_back(event);
}

void Junior::EventManager::SetEventProcessingCap(unsigned processingCap)
{
	eventProcessingCap_ = processingCap;
}

unsigned Junior::EventManager::GetEventProcessingCap() const
{
	return eventProcessingCap_;
}