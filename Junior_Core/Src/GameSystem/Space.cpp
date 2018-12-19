/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Space.cpp
* Description: Manages the levels inside the space
* Created: 18-Dec-2018
* Last Modified: 18-Dec-2018
*/

// Includes 
#include "Space.h"

namespace Junior
{
	// Public Member Functions
	Space::Space(const char* name)
		: GameSystem(name), currentLevel_(nullptr), nextLevel_(nullptr)
	{}

	bool Space::Load()
	{
		return true;
	}

	bool Space::Initialize()
	{
		return true;
	}

	void Space::Update(double)
	{

	}

	void Space::Render()
	{

	}

	void Space::Shutdown()
	{

	}

	void Space::Unload()
	{

	}

	void Space::NextLevel(Level* level)
	{
		nextLevel_ = level;
	}

	void Space::RestartLevel()
	{

	}
}