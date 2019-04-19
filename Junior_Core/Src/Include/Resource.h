/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* Date Created: 11 Sep 2018
* Last Modified: 17 Apr 2019
* File Name: Resource.h
* Description: Defines the resource struct so the Resource Manager can keep track of all of the resources used
*/

#pragma once

// Includes //
#include <string> // std::string

namespace Junior
{
	class Resource
	{
	private:
		// Public Member Variables

		// The original resource that we are using from
		Resource* original_;
	public:
		// Public Member Functions

		// Constructor
		Resource();
		// Copy Constructor
		Resource(Resource& other);
		// Destructor
		virtual ~Resource();
		// Returns: The resource's directory
		const std::string& GetResourceDir() const;
		// Returns: How many other resources are using this original
		unsigned GetResourceCount() const;
	protected:
		// Protected Member Variables

		// How many resources are using this
		unsigned resourceShareCount_;
		// The directory to the resource
		std::string resourceDir_;
		
		// Protected Member Functions

		// Sets up the resource to be loaded from a disk
		// Should be called by children classes everytime they call
		// LoadFromDisk
		// Params:
		//	fileDir: The file directory to load from
		virtual void LoadFromDisk(const std::string& fileDir);
		// Cleans up the resource
		virtual void CleanUp() = 0;
	};
}