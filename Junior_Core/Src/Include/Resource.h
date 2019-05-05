/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* Date Created: 11 Sep 2018
* Last Modified: 26 Apr 2019
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
		// Private Member Variables

		// The original resource that we are using from
		Resource* original_;
	public:
		// Public Member Functions

		// Constructor
		Resource();
		// Copy Constructor
		// Params:
		//	other: The other resource we are copying from
		Resource(const Resource& other);
		// Destructor
		virtual ~Resource();
		// Shares this resource to another resource
		// Returns: A copy of this resource
		template <class T>
		T* ShareResource()
		{
			const T* castedThis = dynamic_cast<const T*>(this);
			T* newResource = new T(*castedThis);
			++resourceShareCount_;
			newResource->original_ = this;
			return newResource;
		}
		// Loads a resource from the file
		// Params:
		//	fileDir: The file we want to load this disk from
		void Load(const std::string& fileDir);
		// Returns: The resource's directory
		const std::string& GetResourceDir() const;
		// Returns: How many other resources are using this original
		unsigned GetResourceCount() const;
		// Cleans up the resource
		virtual void CleanUp();
	protected:
		// Protected Member Variables
		// Sets up the resource to be loaded from a disk
		// Should be called by children classes everytime they call
		// LoadFromDisk
		// Params:
		//	fileDir: The file directory to load from
		virtual void LoadFromDisk(const std::string& fileDir);

		// How many resources are using this
		unsigned resourceShareCount_;
		// The directory to the resource
		std::string resourceDir_;
	};

}