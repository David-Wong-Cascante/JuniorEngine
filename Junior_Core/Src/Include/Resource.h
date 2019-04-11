/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* Date Created: 11-Sep-2018
* Last Modified: 29-Oct-2018
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
	public:
		// Public Class Variables //
		int resourceShareCount_;
		std::string resourceDir;
		
		// Public Member Functions //
		virtual ~Resource()
		{

		}
	protected:
		// Protected Member Functions //
		virtual void LoadFromDisk(std::string resourceDir) = 0;
		virtual void CleanUp() = 0;
	};
}