#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Particle.h
* Description: Defines a particle's properties inside an emitter
* Created: 6 May 2018
* Last Modified: 6 May 2019
*/

// Includes
#include "Vec3.h"			// Vector 3

namespace Junior
{
	struct Particle
	{
		// Public Member Variables

		// ATTRIBUTES

		// The particle's position
		Vec3 position_;
		// The particle's velocity
		Vec3 velocity_;
		// Color of particle
		Vec3 color_;
		// Where x and y are the translation and (z, w) is the scale
		Vec3 uvTranslationAndScale_;
		// Size of particle
		float size_;
		// The particle's lifetime
		float lifeTime_;
		// The particle's age compared to the life time
		float age_;

		// Constructor
		Particle()
			: position_(0.0f, 0.0f, 0.0f), velocity_(0.0f, 0.0f, 0.0f), color_(0.0f, 0.0f, 0.0f), 
			  uvTranslationAndScale_(0.0f, 0.0f, 1.0f, 1.0f), size_(0), lifeTime_(0), age_(0)
		{
		}
	};
}