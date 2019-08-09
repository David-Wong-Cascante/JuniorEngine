#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Event.h
* Description: Event data
* Created: 7 Aug 2019
* Last Modified: 8 Aug 2019
*/

// Includes
#include <string>			// Strings

namespace Junior
{
	struct Event
	{
		// Public Member Variables

		// The name of the event
		std::string name_;

		// Public Member Functions

		// Constructor
		// Params:
		//	name: The name of the event we are using
		Event(const std::string& name)
			: name_(name)
		{
		}
	};
}