/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Event.h
* Description: Event data
* Created: 7 Aug 2019
* Last Modified: 7 Aug 2019
*/

// Includes
#include <string>			// Strings

namespace Junior
{
	struct Event
	{
		// Public Static Variables
		// General event names we can use
		static const std::string WindowSizeChange;

		// Public Member Variables
		std::string name_;
	};

	// Intiailize the Event static variables
	const std::string Event::WindowSizeChange = "WindowSizeChange";
}