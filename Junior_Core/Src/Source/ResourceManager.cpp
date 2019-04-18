/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* Date Created: 11-Sep-2018
* Last Modified: 17 Apr 2019
* File Name: ResourceManager.h
* Description: Describes the Resource Manager
*/

// Includes
#include "ResourceManager.h"

// Private Member Functions
Junior::ResourceManager::ResourceManager()
{
}

Junior::ResourceManager::ResourceManager(const ResourceManager&)
{
}

Junior::ResourceManager::~ResourceManager()
{
	// Go through every resource and delete it
	for (auto begin = resources_.begin(); begin != resources_.end(); ++begin)
	{
		delete begin->second;
	}

	resources_.clear();
}

// Public Static Member Functions
void Junior::ResourceManager::AddResource(Junior::Resource* resource)
{
	/*std::pair<std::string, Resource*> pair(resource->GetResourceDir(), resource);
	resources_.insert(pair);*/
	resources_[resource->GetResourceDir()] = resource;
}

void Junior::ResourceManager::RemoveResource(Junior::Resource const* resource)
{
	resources_.erase(resource->GetResourceDir());
}

void Junior::ResourceManager::RemoveResource(const std::string& resourceDir)
{
	resources_.erase(resourceDir);
}

Junior::ResourceManager& Junior::ResourceManager::GetInstance()
{
	static ResourceManager manager;
	return manager;
}