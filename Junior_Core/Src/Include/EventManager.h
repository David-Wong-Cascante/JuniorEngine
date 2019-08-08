/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: EventManager.h
* Description: Dispatches events to objects throughout the game
* Created: 7 Aug 2019
* Last Modified: 7 Aug 2019
*/

// Includes 
#include "GameSystem.h"			// Game System
#include <string>				// Strings
#include <list>					// Linked List
#include <unordered_map>		// Unordered map
#include <vector>				// Vector

namespace Junior
{
	// Class Forward Declarations
	struct Event;

	// Type Definitions

	// Defining the function pointer objects should use with this event
	// Params:
	//	object: The object hooked to this callback function
	//	calledEvent: The event that fired this callback function
	typedef void (*EventCallback)(void* object, Event* calledEvent);
	// The list that connects a single function pointer to multiple objects
	typedef std::unordered_map<EventCallback, std::vector<void*>> CallbackDispatcher;

	class EventManager : public GameSystem
	{
	private:
		// Private Member Variables

		// The map storing event names to the objects listening to the that event data
		std::unordered_map<std::string, CallbackDispatcher> callbackMap_;
		// The events we need to process
		std::list<Event*> unprocessedEvents_;
		// How many events do we process per frame
		// If the amount is zero, then we process all events in the current frame
		unsigned eventProcessingCap_;

		// Private Member Functions

		// Private Constructor
		EventManager();
		// Creates a new map slot for an event
		// Params:
		//	name: The name of the event we want to create a slot for
		// Returns: The callback dispatcher created as a result of creating the slot for the event
		CallbackDispatcher& CreateEventMapSlot(const std::string& name);
		// Fires the dispatched callback function with the incoming event
		// Params:
		//	event: The sent event we are trying to dispatch the callback for
		void DispatchEvent(Event* event);

	public:
		// Public Static Functions
		EventManager& GetInstance() const;

		// Public Member Functions

		// Loads the event manager
		// Returns: Whether the event manager succeded in loading assets among other things
		bool Load() override;
		// Initializes the game system
		// Returns: Whether the system succeded initializing
		bool Initialize() override;
		// Updates the event manager
		// Params:
		//	dt: The delta time between frames when updating this system
		void Update(double dt) override;
		// Renders the system
		void Render() override;
		// Shuts down the event manager
		void Shutdown() override;
		// Unloads all of the assets of the event manager
		void Unload() override;

		// Connects a object to an event callback
		// Params:
		//	name: The name of the event
		//	object: The object we want to hook up
		//	callback: The event callback function we want to call
		void Subscribe(const std::string& name, void* object, const EventCallback callback);
		// Disconnects an object from an event callback
		// Params:
		//	name: The name of the event we want to disconnect from
		//	object: The object we want to disconnect from the callback
		//	callback: The callback the object is disconnected to
		void Unsubscribe(const std::string& name, const void* object, const EventCallback callback);
		// Sends the event to the event manager
		// Params:
		//	event: The event that is send to the event manager to dispatch across all objects in the manager
		//		   WARNING: The manager will try to delete this event after it is done with it
		void SendEvent(const Event* event);
		// Sets the event processing cap
		// Params:
		//	processingCap: How many events are processed per frame
		void SetEventProcessingCap(unsigned processingCap);
		// Gets how many events are processed per frame
		// Returns: How many events are we processed per frame
		unsigned GetEventProcessingCap() const;

	};
}