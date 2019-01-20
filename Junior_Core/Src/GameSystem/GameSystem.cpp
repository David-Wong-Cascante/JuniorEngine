/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: GameSystem.cpp
* Description: Defines a general manner to organize all the systems
* Created: 18-Dec-2018
* Last Modified: 18-Dec-2018
*/

// Includes
#include "GameSystem.h"

#include <iostream>			// Output stream

// Public Member Functions
namespace Junior
{
	GameSystem::GameSystem(const char* name)
		: name_(name)
	{}

	void GameSystemAssert(bool success, const char* errorMessage)
	{
		if (!success)
		{
			std::cout << "[ERROR]: " << errorMessage << std::endl;
		}
	}

	const char* GameSystem::GetName() const
	{
		return name_;
	}
}