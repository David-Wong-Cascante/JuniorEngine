#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: ComponentContainer.h
* Description: Wraps around a component
* Created: 8 Apr 2019
* Last Modified: 18 Jul 2019
*/

// Includes
#include "Serializable.h"			// Component

namespace Junior
{
	// Forward Declarations
	class MemoryManager;
	class GameObject;

	class ComponentContainer : public Serializable
	{
	protected:
		// Protected Class Variables
		bool updateable_;
		GameObject* owner_;
		std::string name_;
		// Protected Member Functions
		// Hide the default constructor
		ComponentContainer();
	public:
		// Public Member Functions

		// Virtual Destructor
		virtual ~ComponentContainer();

		// Classes inheriting from Component Container should define these functions

		// Initializes the component
		virtual void Initialize() {};
		// Updates the component at a fixed rate
		// Params:
		//	ms: The fixed delta time between frames
		virtual void FixedUpdate(double ms) {}
		// Update the component
		// Params:
		//	ms: The delta time between frames
		virtual void Update(double ms) {};
		// Unloads the component
		virtual void Unload() {};
		// Serializes the component
		// Params:
		//	parser: The parser we are using to write the component
		virtual void Serialize(Parser& parser) const override;
		// Deserializes the component
		// Params:
		//	parser: The parser we are using to read the component
		virtual void Deserialize(Parser& parser) override;
		// Clones the component
		// Returns: A clone of the component
		virtual ComponentContainer* Clone() const = 0;
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