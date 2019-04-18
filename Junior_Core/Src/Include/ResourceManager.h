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
		// Private Class Variables
		std::unordered_map<std::string, Resource*> resources_;

		// Hide the constructors
		
		// Constructor
		ResourceManager();
		// Copy Constructor
		// Params:
		//	other: The other resource manager
		ResourceManager(const ResourceManager& other);
		// Destructor
		~ResourceManager();
	public:
		// Public Static Member Functions // 
		// Adds a resource to the manager
		// Params:
		//	resource: The resource we are adding
		void AddResource(Resource* resource);
		// Removes a resource from the manager
		// Params:
		//	resource: The resource we are removing
		void RemoveResource(Resource const* resource);
		// Removes a resource from the manager
		// Params:
		//	resourceDir: The directory of the resoruce we are trying to remove
		void RemoveResource(const std::string& resourceDir);
		// Gets a resource from the manager
		// Params:
		//	resourceDir: The resource
		template <typename T>
		T* GetResource(const std::string& resourceDir)
		{
			// Attemmpting to find the resource
			auto iter = resources_.find(resourceDir);
			Resource* resource = iter->second;
			T* typedResource;
			if(resource)
			{
				// We found a resource with that name, so we are going to attempt and cast it to T
				typedResource = dynamic_cast<T*>(resource);
				if (typedResource)
				{
					return new T(*typedResource);
				}
			}
			// Else we didn't find the map so we need to create it 
			typedResource = new T;
			typedResource->LoadFromDisk(resourceDir);
			AddResource(typedResource);

			return new T(*typedResource);
		}

		// Returns: The instance of the resource manager
		static ResourceManager& GetInstance();
	};
}