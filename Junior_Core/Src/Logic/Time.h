#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Time.h
* Description: Declare the Time system for our engine
* Created: 20-Apr-2018
* Last Modified: 29-Oct-2018
*/

namespace Junior
{
	class Time
	{
		public:
			// Public Static Class Variables //
			double static deltaTime;
			double static timeRan;
			double static timeScale;
			double static scaledDeltaTime;
			double static prevTime, currTime;
			// Public Static Functions //
			void static Update();
	};
}