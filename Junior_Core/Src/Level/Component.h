#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Component.h
* Description: Define the general component class for the rest of the others
* Created: 28-Apr-2018
* Last Modified: 13-Feb-2019
*/

// Includes
#include <string>				// String

namespace Junior
{
	// Forward Declarations //
	class GameObject;
	class MemoryManager;

	class Component
	{
	protected:
		// Protected Class Variables //
		bool updateable_;
		GameObject* owner_;
		std::string name_;
	public:
		// Public Member Functions
		Component(std::string name, bool updatable = true);
		~Component();
		// Classes inheriting from Component should define this function
		virtual void Initialize() = 0;
		virtual void Update(double ms) = 0;
		virtual void Clean(MemoryManager* manager) = 0;

		// Sets the component's owner
		// Parmas:
		//	cog: The parent we want to set this component to
		void SetOwner(GameObject* cog);
		// Get the component's type name
		// Returns: The component type
		const std::string GetTypeName() const;
		// Is the object updateable
		// Returns: Whether the render job should be updated
		bool IsUpdateable() const;
	};
}