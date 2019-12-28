#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: PlayerController.h
* Description: Makes the player be able to move around
* Created: 28 Jul 2019
* Last Modified: 28 Jul 2019
*/

// Includes
#include <Component.h>			// Component

namespace Junior
{
	// Forward Declarations
	class Transform;
	class Physics;
	class Animator;
	struct JoystickData;
}


namespace JuniorGame
{
	class PlayerController : public Junior::Component<PlayerController>
	{
	private:
		// Private Member Variables

		// The object's transform
		Junior::Transform* transform_;
		// The object's physics
		Junior::Physics* physics_;
		// The object's animator
		Junior::Animator* animator_;
		// The player's joystick data
		const Junior::JoystickData* joystickData_;

	public:
		// Public Member Functions

		// Constructor
		PlayerController();
		// Copy Constructor
		// Params:
		//	other: The other player controller we are copying from
		PlayerController(const PlayerController& other);
		// Initializes the component
		void Initialize() override;
		// Updates the component
		// Params:
		//	dt: The delta time between frames
		void Update(double dt) override;
		// Serializes the component to a file
		// Params:
		//	parser: The parser used to serialize the object to the file
		void Serialize(Junior::Parser& parser) const override;
		// Reads the component off from a file
		// Params:
		//	parser: The parser used to deserialize the object from the file
		void Deserialize(Junior::Parser& parser) override;
	};
}
