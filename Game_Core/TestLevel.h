/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: TestLevel.h
* Description: Test level for object management
* Created: 20 Dec 2018
* Last Modified: 28 Jul 2019
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
}

namespace JuniorGame
{
	class TestLevel : public Junior::Level
	{
	private:
		// Keeping track of time
		double timer_;
		// Whether we deleted the second object
		bool deletedObject2_;
		// Lerping the joystick position
		Junior::Vec3 lerpJoystickPosition;
		// The transforms of the game objects
		Junior::Transform *transform_, *transform2_, *cameraTransform_;
		// The player's physics
		Junior::Physics* playerPhysics_;
		// The spawned game objects
		Junior::GameObject *cog_, *cog2_, *camera_;
		// Whether the test level is marked for a restart or not
		bool restart_;
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