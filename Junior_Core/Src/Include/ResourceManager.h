/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* Date Created: 11 Sep 2018
* Last Modified: 18 Apr 2019
* File Name: ResourceManager.h
* Description: Defines a static class in charge of keeping track of resources via an unordered map
*/

#pragma once

// Includes
#include <unordered_map>			// std::unordered_map
#include "GameSystem.h"				// Game System


namespace Junior
{
	// Forward Declarations
	class Resource;

	class ResourceManager : public GameSystem
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
		// Public Member Functions
		// Loads the Resource Manager
		bool Load() override;
		// Initialize the Resource Manager
		bool Initialize() override;
		// Updates the Resource Manager
		void Update(double dt) override;
		// Debug Renders the Resource Manager
		void Render() override;
		// Shutsdown the the Resource manager
		void Shutdown() override;
		// Unloads the Resource Manager
		void Unload() override;
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
			T* typedResource;
			if (iter != resources_.end())
			{
				Resource* resource = iter->second;
				if(resource)
				{
					// We found a resource with that name, so we are going to attempt and cast it to T
					typedResource = dynamic_cast<T*>(resource);
					if (typedResource)
					{
						return new T(*typedResource);
					}
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