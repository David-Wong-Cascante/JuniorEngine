/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: ParticleEmitter.cpp
* Description: Emits the particles
* Created: 6 May 2018
* Last Modified: 6 May 2019
*/

// Includes
#include "ParticleEmitter.h"
#include "GameObject.h"				// Game Object
#include "Transform.h"				// Transform

// Private Member Functions

void Junior::ParticleEmitter::SpawnParticles()
{
	// Spawn particles by updating data on dead particles
	// -> Find each dead particle that is not past the vector's range
	for (size_t i = 0; i < particleSpawnCount_; ++i)
	{
		// If the index is outside of the range of the vector, then quit spawning particles
		if (i >= particles_.size())
			return;

		// Otherwise, update the data
		Particle& particle = particles_.at(i);
		// TODO: Make the initial properties random
		particle.age_ = maxLifeTime_;
		particle.color_ = startColor_;
		particle.size_ = startSize_;
		particle.position_ = transform_->GetLocalTranslation();
	}
}

// Public Member Functions

Junior::ParticleEmitter::ParticleEmitter()
	: particleSpawnTimer_(0.0f), maxLifeTime_(0), minLifeTime_(0),
	  maxParticles_(0), numParticles_(0), particleSpawnCount_(0), particleSpawnWait_(0), loop_(false), particles_(),
	  colorInterpolate_(nullptr), sizeInterpolate_(nullptr)
{
}

Junior::ParticleEmitter::ParticleEmitter(const ParticleEmitter& other)
	: particleSpawnCount_(other.particleSpawnCount_), maxLifeTime_(other.maxLifeTime_), minLifeTime_(other.minLifeTime_),
	maxParticles_(other.maxParticles_), numParticles_(other.numParticles_), particleSpawnWait_(other.particleSpawnWait_),
	particleSpawnTimer_(0.0f), loop_(other.loop_), particles_(), colorInterpolate_(other.colorInterpolate_),
	sizeInterpolate_(other.sizeInterpolate_)
{
}

void Junior::ParticleEmitter::Initialize()
{
	// Get the transform
	transform_ = owner_->GetComponent<Transform>();
	// Reset the particles
	particles_.clear();
	particles_.resize(maxParticles_);
	// Reset the spawn timer
	particleSpawnTimer_ = 0.0f;
	// Spawn particles
	SpawnParticles();
}

void Junior::ParticleEmitter::Update(double dt)
{
	// Sort dead and live particles
	for (auto particle = particles_.begin(); particle != particles_.begin() + numParticles_;)
	{
		// Get the particle
		Particle& current = (*particle);
		// Decrement the age by the time passed
		current.age_ -= static_cast<float>(dt);
		// If the age is less than zero, then the the particle is dead
		if (current.age_ <= 0.0f)
		{
			// -> Get the last particle live
			Particle lastCurrent = current;
			Particle& swappedParticle = *(particles_.begin() + numParticles_ - 1);
			
			current = swappedParticle;
			swappedParticle = lastCurrent;
			// If the particle is dead, then swap this dead particle into the last live particle we have (at the end of the list)
			// Decrement the number of particles we have because we found one dead
			--numParticles_;
		}
		else
		{
			// Otherwise, we are going to keep moving through the list
			++particle;
		}
	}

	// Now, update the particles
	for (auto particle = particles_.begin(); particle != particles_.begin() + numParticles_;)
	{
		// Get the current particle
		Particle& current = (*particle);
		// Update the current position
		current.position_ = current.velocity_ * static_cast<float>(dt);
		// Change the color of the particle
		current.color_ = colorInterpolate_(startColor_, endColor_, 1 - (current.age_ / current.lifeTime_));
		// Change the size of the particle
		current.size_ = sizeInterpolate_(startSize_, endingSize_, 1 - (current.age_ / current.lifeTime_));
	}

	// Finally, check if we need to spawn any particles
	particleSpawnTimer_ += static_cast<float>(dt);
	if (particleSpawnTimer_ >= particleSpawnWait_ && loop_)
	{
		particleSpawnTimer_ -= particleSpawnWait_;
		// Start spawning particles
		SpawnParticles();
	}
}

void Junior::ParticleEmitter::Unload()
{
}