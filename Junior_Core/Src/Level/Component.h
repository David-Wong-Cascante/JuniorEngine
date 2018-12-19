#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Component.h
* Description: Define the general component class for the rest of the others
* Created: 28-Apr-2018
* Last Modified: 11-Dec-2018
*/

namespace Junior
{
	// Forward Declarations //
	class GameObject;
	class MemoryManager;
	class Graphics;
	struct RenderJob;

	enum ComponentType
	{
		NONE = 0,
		TRANSFORM,
		SPRITE,
		TEXT,
	};


	class Component
	{
	protected:
		// Protected Class Variables //
		bool updateable_;
		GameObject* owner_;
		RenderJob* renderJob_;
		Graphics* currGraphics_;
		ComponentType type_;
	public:
		// Public Member Functions
		Component(Junior::Graphics* graphics, bool updatable = true);
		~Component();
		// Classes inheriting from Component should define this function
		virtual void Initialize() = 0;
		virtual void Update(double ms) = 0;
		virtual void Clean(MemoryManager* manager) = 0;

		// Sets the component's owner
		// Parmas:
		//	cog: The parent we want to set this component to
		void SetOwner(GameObject* cog);
		// Get the component's type
		// Returns: The component type
		const ComponentType GetType() const;
		// Is the object updateable
		// Returns: Whether the render job should be updated
		bool IsUpdateable() const;
		// Get the Render Job
		// Returns: The render job
		const RenderJob* GetRenderJob() const;
	};
}