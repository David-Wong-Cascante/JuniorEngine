/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* Date Created: 11-Sep-2018
* Last Modified: 29-Oct-2018
* File Name: ResourceManager.h
* Description: Describes the Resource Manager
*/

// Includes //
#include "ResourceManager.h"

// Private Static Class Variables //
std::unordered_map<std::string, Junior::Resource*> Junior::ResourceManager::resources_;

// Public Static Member Functions //
void Junior::ResourceManager::AddResource(Junior::Resource* resource)
{
	resources_.insert({ resource->resourceDir, resource });
}

void Junior::ResourceManager::RemoveResource(Junior::Resource const* resource)
{
	resources_.erase(resource->resourceDir);
}

void Junior::ResourceManager::RemoveResource(const std::string resourceDir)
{
	resources_.erase(resourceDir);
}

Junior::Resource* Junior::ResourceManager::GetResource(const std::string resourceDir)
{
	return resources_[resourceDir];
}