#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Time.h
* Description: Declare the Time system for our engine
* Created: 20-Apr-2018
* Last Modified: 29-Oct-2018
*/

// Includes
#include "GameSystem.h"			// Game System

namespace Junior
{
	class Time : public GameSystem
	{
	private:
			// Private Class Variables //
			double deltaTime_;
			double timeRan_;
			double timeScale_;
			double scaledDeltaTime_;
			double prevTime_, currTime_;
		public:
			// Public Functions //
			// Constructor
			Time();
			// Loads any resources if necessary
			bool Load() override;
			// Initializes the clock
			bool Initialize() override;
			// Debug Render
			void Render() override;
			// Updates the time class
			void Update(double dt) override;
			// Shuts down the time
			void Shutdown() override;
			// Unloads the time class
			void Unload() override;
			// Mutators
			void SetTimeScale(double timeScale);
			// Accessors
			// Returns the time between frames
			double GetDeltaTime() const;
			// Returns the total time ran in the application
			double GetTimeRan() const;
			// Returns the time scale
			double GetTimeScale() const;
			// Returns the time between frames scaled
			double GetScaledDeltaTime() const;

			// Returns a singleton instance of Time
			static Time& GetInstance();
	};
}