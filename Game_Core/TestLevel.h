/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: TestLevel.h
* Description: Test level for object management
* Created: 20 Dec 2018
* Last Modified: 7 July 2019
*/

// Includes
#include "Level.h"
#include "Vec3.h"

namespace Junior
{
	// Forward Declarations
	class Transform;
	class Physics;
	class GameObject;
	struct JoystickData;

	class TestLevel : public Level
	{
	private:
		// Keeping track of time
		double timer_;
		// Whether we deleted the second object
		bool deletedObject2_;
		// Lerping the joystick position
		Vec3 lerpJoystickPosition;
		// The transforms of the game objects
		Transform *transform_, *transform2_, *cameraTransform_;
		// The player's physics
		Physics* playerPhysics_;
		// The spawned game objects
		GameObject *cog_, *cog2_, *camera_;
		// The joystick data
		const JoystickData* playerJoystick_;
	public:
		// Constructor
		TestLevel();
		// Loads the level
		bool Load() override;
		// Initializes the level
		bool Initialize() override;
		// Updates the level
		//	dt: The time in between frames
		void Update(double dt) override;
		// Shutsdown the level
		void Shutdown() override;
		// Unloads the level
		void Unload() override;
	};
}