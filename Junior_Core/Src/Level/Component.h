#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Component.h
* Description: Define the general component class for the rest of the others
* Created: 28-Apr-2018
* Last Modified: 8-Apr-2019
*/

// Includes
#include <string>					// String
#include "ComponentContainer.h"		// Component Container
#include "Parser.h"					// Parser

namespace Junior
{
	// Forward Declarations //
	class GameObject;
	class MemoryManager;

	template <class T>
	class Component : public ComponentContainer
	{
	public:
		// Public Member Functions
		Component(std::string name, bool updatable = true)
		{
			owner_ = nullptr;
			name_ = name;
			updateable_ = updatable;
		}

		~Component() override
		{
		}
		// Classes inheriting from Component should define this function
		virtual void Initialize() override = 0;
		virtual void Update(double ms) override = 0;
		virtual void Unload(MemoryManager* manager) override = 0;
		virtual void Serialize(Parser& parser) override
		{
		}
		virtual void Deserialize(Parser& parser) override
		{
		}
	};
}