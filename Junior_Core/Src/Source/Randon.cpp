/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Random.h
* Description: Describes a random function
* Created: 13 May 2019
* Last Modified: 13 May 2019
*/

// Includes
#include "Random.h"			// Random
// For the meanwhile, using the standard C++ random
#include <stdlib.h>			// C random
#include <time.h>			// C time

// Public Member Functions

Junior::Random::Random()
{
	Seed(0);
}

void Junior::Random::Seed(unsigned seed) const
{
	srand(seed);
}

unsigned Junior::Random::RandomInt() const
{
	return rand();
}

unsigned Junior::Random::RandomInt(unsigned min, unsigned max) const
{
	return min + rand() % (max - min);
}

float Junior::Random::RandomFloat() const
{
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

// Source: https://stackoverflow.com/questions/686353/random-float-number-generation
float Junior::Random::RandomFloat(float min, float max) const
{
	return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));
}