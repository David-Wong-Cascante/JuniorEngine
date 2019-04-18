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

// Private Member Functions
Junior::ResourceManager::ResourceManager()
	: GameSystem("ResourceManager")
{
}

Junior::ResourceManager::ResourceManager(const ResourceManager&)
	: GameSystem("ResourceManager")
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