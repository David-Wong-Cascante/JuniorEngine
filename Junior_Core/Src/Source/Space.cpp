/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Space.cpp
* Description: Manages the levels inside the space
* Created: 18-Dec-2018
* Last Modified: 20-Dec-2018
*/

// Includes 
#include "Space.h"

#include "Level.h"						// Level
#include "GameObjectManager.h"			// Object Manager

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

	void Space::Update(double dt)
	{
		// If the next level exists, then move on the next level
		if (nextLevel_)
		{
			MoveLevels();
			return;
		}

		// Update the current level
		currentLevel_->Update(dt);
	}

	void Space::Render()
	{
		
	}

	void Space::Shutdown()
	{
		// Shutdown both levels
		if (currentLevel_)
		{
			currentLevel_->Shutdown();
		}

		if (nextLevel_)
		{
			nextLevel_->Shutdown();
		}
	}

	void Space::Unload()
	{
		// Delete both levels
		if (currentLevel_)
		{
			currentLevel_->Unload();
			delete currentLevel_;
#ifdef _DEBUG
			currentLevel_ = nullptr;
#endif
		}

		if (nextLevel_)
		{
			nextLevel_->Unload();
			delete nextLevel_;
#ifdef _DEBUG
			nextLevel_ = nullptr;
#endif
		}
	}

	void Space::NextLevel(Level* level)
	{
		if (nextLevel_)
		{
			nextLevel_->SetOwner(nullptr);
		}

		nextLevel_ = level;
		nextLevel_->SetOwner(this);
	}

	void Space::RestartLevel()
	{
		currentLevel_->Shutdown();
		currentLevel_->Unload();
		// Unload all the objects from the game manager
		GameObjectManager::GetInstance().Shutdown();
		GameObjectManager::GetInstance().Unload();
		GameObjectManager::GetInstance().Load();
		GameObjectManager::GetInstance().Initialize();
		GameSystemAssert(currentLevel_->Load(), "Current level failed to load!");
		GameSystemAssert(currentLevel_->Initialize(), "Current level failed to initialize!");
	}

	// Private Member Functions
	void Space::MoveLevels()
	{
		// If the past level exists, then shutdown and unload the previous level
		if (currentLevel_)
		{
			currentLevel_->Shutdown();
			currentLevel_->Unload();
			delete currentLevel_;
		}

		// Construct the current level
		currentLevel_ = nextLevel_;
		nextLevel_ = nullptr;
		GameSystemAssert(currentLevel_->Load(), "Current Level failed to load!");
		GameSystemAssert(currentLevel_->Initialize(), "Current level failed to initialize!");
	}
}