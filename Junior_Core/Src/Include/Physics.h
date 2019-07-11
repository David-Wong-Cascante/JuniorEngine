#pragma once
/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: Physics.h
 * Description: Takes care of any physical motion
 * Created: 7 July 2019
 * Last Modified: 7 July 2019
*/

// Includes
#include "Component.h"				// Component
#include "Serializable.h"			// Serializable
#include "Vec3.h"					// Vec3

namespace Junior
{
	// Class Declarations
	class Transform;

	class Physics : public Component<Physics>
	{
	private:
		// Private Member Variables

		// The inverse of the object's mass
		float inverseMass_;
		// The rotational velocity the object has
		float angularVelocity_;
		// The acceleration the object has
		Vec3 acceleration_;
		// The velocity the object has
		Vec3 velocity_;
		// The position before we moved the player using the velocity
		Vec3 prevPosition_;
		// The object's transform
		Transform* transform_;
	public:

		// Public Member Functions

		// Constructor
		// Params:
		//	mass: The mass of the object in kilograms
		Physics(float mass = 1.0f);
		// Copy Constructor
		// Params:
		//	other: The other physics component we are copying from
		Physics(const Physics& other);
		// Initializes the component
		void Initialize() override;
		// Updates the component
		// Params:
		//	dt: The delta time between frames
		void Update(double dt) override;
		// Cleans the component
		void Unload() override;
		// Serializes the physics component to a file
		// Params:
		//	parser: The parser we are using to save to a file
		void Serialize(Parser& parser) const override;
		// Deserializes the physics from a file
		// Params:
		//	parser: The parser wer are using to load from a file
		void Deserialize(Parser& parser) override;
		// Sets the mass of the object
		// Params:
		//	mass: The mass of the object
		void SetMass(float mass);
		// Sets the velocity of the object
		// Params:
		//	velocity: The current velocity of the object
		void SetVelocity(const Vec3& velocity);
		// Sets the angular velocity of the object
		// Params:
		//	angular: The object's angular velocity
		void SetAngularVelocity(float angular);
		// Adds a one-time force to the object
		// Params:
		//	force: The force we are using to move this object
		void AddForce(const Vec3& force);
		// Gets the velocity of the object
		// Returns: The object's velocity
		const Vec3& GetVelocity() const;
		// Gets the angular velocity of the object
		// Returns: The object's angular velocity
		float GetAngularVelocity() const;
		// Gets the previous position of the object before performing physics calculations on it
		// Returns: The object's previous position
		const Vec3& GetPrevPosition() const;
	};
}