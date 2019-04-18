#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Component.h
* Description: Define the general component class for the rest of the others
* Created: 28 Apr 2018
* Last Modified: 18 Apr 2019
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
		Component(bool updatable = true)
		{
			owner_ = nullptr;
			std::string fullName = typeid(T).name();
			std::string shortName = fullName.substr(6, fullName.length());
			name_ = shortName;
			updateable_ = updatable;
		}

		~Component() override
		{
		}
		// Classes inheriting from Component should define this function
		virtual void Initialize() override = 0;
		virtual void Update(double ms) override = 0;
		virtual void Unload() override = 0;
		virtual void Serialize(Parser& parser) override
		{
		}
		virtual void Deserialize(Parser& parser) override
		{
		}

		// Clones the component
		ComponentContainer* Clone() const override
		{
			return new T(*static_cast<const T*>(this));
		}
	};
}