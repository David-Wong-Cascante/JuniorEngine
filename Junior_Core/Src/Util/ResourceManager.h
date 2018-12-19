/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* Date Created: 11-Sep-2018
* Last Modified: 29-Oct-2018
* File Name: ResourceManager.h
* Description: Defines a static class in charge of keeping track of resources via an unordered map
*/

#pragma once

// Includes //
#include <unordered_map> // std::unordered_map
#include "Resource.h" // Resource


namespace Junior
{
	class ResourceManager
	{
	private:
		// Private Static Class Variables //
		static std::unordered_map<std::string, Resource*> resources_;
	public:
		// Public Static Member Functions // 
		static void AddResource(Resource* resource);
		static void RemoveResource(Resource const* resource);
		static void RemoveResource(const std::string resourceDir);
		static Resource* GetResource(const std::string resourceDir);
	};
}