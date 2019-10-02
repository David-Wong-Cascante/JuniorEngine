/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Space.cpp
* Description: Manages the levels inside the space
* Created: 18 Dec 2018
* Last Modified: 2 Oct 2019
*/

// Includes 
#include "Space.h"

#include "Level.h"						// Level

namespace Junior
{
	// Public Member Functions
	Space::Space(const char* name)
		: GameSystem(name), markedForRestart_(false), currentLevel_(nullptr), nextLevel_(nullptr)
	{}

	bool Space::Load()
	{
		manager_.Load();
		return true;
	}

	bool Space::Initialize()
	{
		manager_.Initialize();
		return true;
	}

	void Space::Update(double dt)
	{
		// Restart the levels if needed
		if (markedForRestart_)
		{
			currentLevel_->Shutdown();
			currentLevel_->Unload();
			// Clear all of the objects in the manager
			manager_.Shutdown();
			manager_.Unload();
			manager_.Load();
			manager_.Initialize();

			GameSystemAssert(currentLevel_->Load(), "Current level failed to load!");
			GameSystemAssert(currentLevel_->Initialize(), "Current level failed to initialize!");

			markedForRestart_ = false;
		}
		
		// If the next level exists, then move on the next level
		if (nextLevel_)
		{
			MoveLevels();
			return;
		}

		// Update the current level
		currentLevel_->Update(dt);
		// Update the objects within the space
		manager_.Update(dt);
	}

	void Space::Render()
	{
		manager_.Render();
	}

	void Space::Shutdown()
	{
		// Shutdown the objects before the spaces themselves
		manager_.Shutdown();
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
		manager_.Unload();
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

	Junior::GameObjectManager* Space::GetObjectManager()
	{
		return &manager_;
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
		markedForRestart_ = true;
	}

	// Private Member Functions
	void Space::MoveLevels()
	{
		// If the past level exists, then shutdown and unload the previous level
		if (currentLevel_)
		{
			// Clear all of the objects in the manager
			manager_.Shutdown();
			manager_.Unload();
			manager_.Load();
			manager_.Initialize();

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