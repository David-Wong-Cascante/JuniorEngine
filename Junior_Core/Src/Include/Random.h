#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Random.h
* Description: Describes a random function
* Created: 13 May 2019
* Last Modified: 13 May 2019
*/

namespace Junior
{
	class Random
	{
	public:
		// Public Member Functions

		// Constructor
		Random();
		// Seeds the RNG
		// Params:
		//	seed: The seed to the random number generator
		void Seed(unsigned seed) const;
		// Generates a random number with no range
		// Returns: The random unbounded integer
		unsigned RandomInt() const;
		// Generates a random number with an includsive range
		// Params:
		//	min: The minimum boundary for the random integer
		//	max: The maximum boundary for the random integer
		// Returns: a random bounded integer
		unsigned RandomInt(unsigned min, unsigned max) const;
		// Returns: A random float from 0 - 1
		float RandomFloat() const;
		// Params:
		//	min: The minimum boundary for the random float
		//	max: The maximum boundary for the random float
		// Returns: A random float within the inclusive boundaries specified
		float RandomFloat(float min, float max) const;
	};
}