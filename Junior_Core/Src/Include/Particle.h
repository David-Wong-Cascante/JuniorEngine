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

		// The particle's position
		Vec3 position_;
		// The particle's velocity
		Vec3 velocity_;
		// Color of particle
		Vec3 color_;
		// Size of particle
		float size_;
		// The particle's lifetime
		float lifeTime_;
		// The particle's age compared to the life time
		float age_;
		// The particle's mass
		float mass_;

		// Constructor
		Particle()
			: position_(), velocity_(), color_(), size_(0), lifeTime_(0), age_(0), mass_(0)
		{
		}
	};
}