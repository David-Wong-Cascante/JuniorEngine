/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* Date Created: 17 Apr 2019
* Last Modified: 26 Apr 2019
* File Name: Resource.cpp
* Description: Defines the resource struct so the Resource Manager can keep track of all of the resources used
*/

// Includes

#include "Resource.h"

// Public Member Functions

Junior::Resource::Resource()
	: resourceDir_(), resourceShareCount_(0), original_(nullptr)
{
}

Junior::Resource::~Resource()
{
	if (original_)
		--original_->resourceShareCount_;
}

void Junior::Resource::LoadFromDisk(const std::string& fileDir)
{
	resourceShareCount_ = 0;
	resourceDir_ = fileDir;
}

const std::string& Junior::Resource::GetResourceDir() const
{
	return resourceDir_;
}

unsigned Junior::Resource::GetResourceCount() const
{
	return resourceShareCount_;
}

void Junior::Resource::CleanUp()
{
}