/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* Date Created: 11 Sep 2018
* Last Modified: 18 Apr 2019
* File Name: ResourceManager.h
* Description: Describes the Resource Manager
*/

// Includes
#include "ResourceManager.h"
#include "Resource.h"			// Resource
#include "Debug.h"				// Debug

// Private Member Functions
Junior::ResourceManager::ResourceManager()
	: GameSystem("ResourceManager"), garbageCollectionDuration_(3.0), garbageCollectionTimer_(0.0)
{
}

Junior::ResourceManager::ResourceManager(const ResourceManager&)
	: GameSystem("ResourceManager"), garbageCollectionDuration_(3.0), garbageCollectionTimer_(0.0)
{
}

bool Junior::ResourceManager::Load()
{
	return true;
}

bool Junior::ResourceManager::Initialize()
{
	return true;
}

void Junior::ResourceManager::Update(double dt)
{
	garbageCollectionTimer_ += dt;
	if (garbageCollectionTimer_ >= garbageCollectionDuration_)
	{
		Debug::GetInstance().PrintLn("RESOURCE GARBAGE COLLECTION TIME!!");
		garbageCollectionTimer_ = 0.0;
		// Check garbage resources
		for (auto begin = resources_.begin(); begin != resources_.end(); )
		{
			if (begin->second->GetResourceCount() == 0)
			{
				// If we found a garbage resource, remove it
				delete begin->second;
				begin = resources_.erase(begin);
			}
			else
			{
				++begin;
			}
		}
	}
}

void Junior::ResourceManager::Render()
{
}

void Junior::ResourceManager::Shutdown()
{
}

void Junior::ResourceManager::Unload()
{
	if (resources_.size() == 0)
		return;
	// Go through every resource and delete it
	for (auto begin = resources_.begin(); begin != resources_.end(); ++begin)
	{
		if (begin->second->GetResourceCount() > 0)
		{
			// If we found a resource still sharing itself to other resources
			Debug::GetInstance().Print(Debug::GetInstance().GetDebugLevelName(DebugLevel::WARNING));
			Debug::GetInstance().Print(begin->second->GetResourceDir());
			Debug::GetInstance().PrintLn(" still has resources attached to it!");
		}
		delete begin->second;
	}

	resources_.clear();
}

Junior::ResourceManager::~ResourceManager()
{
	Unload();
}

// Public Static Member Functions
void Junior::ResourceManager::AddResource(Junior::Resource* resource)
{
	resources_[resource->GetResourceDir()] = resource;
}

void Junior::ResourceManager::RemoveResource(const std::string& resourceDir)
{
	delete resources_[resourceDir];
	resources_.erase(resourceDir);
}

Junior::ResourceManager& Junior::ResourceManager::GetInstance()
{
	static ResourceManager manager;
	return manager;
}