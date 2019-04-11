/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: TestLevel.h
* Description: Test level for object management
* Created: 20-Dec-2018
* Last Modified: 20-Dec-2018
*/

// Includes
#include "Level.h"
#include "Vec3.h"

namespace Junior
{
	// Forward Declarations
	class Transform;
	class GameObject;
	struct JoystickData;

	class TestLevel : public Level
	{
	private:
		double timer_;
		bool deletedObject2_;
		Vec3 lerpJoystickPosition;
		Transform *transform_, *transform2_, *cameraTransform_;
		GameObject *cog_, *cog2_, *camera_;
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
		// Unloads the level
		void Unload() override;
	};
}