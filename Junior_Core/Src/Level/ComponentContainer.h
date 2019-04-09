#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: ComponentContainer.h
* Description: Wraps around a component
* Created: 8-Apr-2019
* Last Modified: 8-Apr-2019
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
		// Classes inheriting from Component Container should define this function
		virtual void Initialize() = 0;
		virtual void Update(double ms) = 0;
		virtual void Unload(MemoryManager* manager) = 0;
		virtual void Serialize(Parser& parser) override = 0 ;
		virtual void Deserialize(Parser& parser) override  = 0;

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

		template<class T>
		T* Clone() const
		{
			const T* castedComponent = reinterpret_cast<const T*>(this);
			return new T(*castedComponent);
		}
	};
}