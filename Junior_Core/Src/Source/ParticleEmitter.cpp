/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: ParticleEmitter.cpp
* Description: Emits the particles
* Created: 6 May 2018
* Last Modified: 10 May 2019
*/

// Includes
#include "ParticleEmitter.h"

#include <math.h>					// atan2
#include "LinearMath.h"				// Linear Math
#include "GameObject.h"				// Game Object
#include "Transform.h"				// Transform
#include "Parser.h"					// Parser

// Global Functions

Junior::Vec3 Junior::Lerp(const Vec3& start, const Vec3& end, float t)
{
	return start + t * (end - start);
}

float Junior::Lerp(const float& start, const float& end, float t)
{
	return start + t * (end - start);
}

// Private Member Functions

void Junior::ParticleEmitter::SpawnParticles()
{
	// Spawn particles by updating data on dead particles
	// -> Find each dead particle that is not past the vector's range
	for (size_t i = 0; i < particleSpawnCount_; ++i)
	{
		// If the index is outside of the range of the vector, then quit spawning particles
		if (numParticles_ >= particles_.size())
			return;

		// Otherwise, update the data
		Particle& particle = particles_.at(numParticles_);
		// The random angle to rotate the intial velocity
		float randVelAngle = random_.RandomFloat(-randomVelocityAngle_ / 2.0f, randomVelocityAngle_ / 2.0f);
		// Find the random velocity that we will spawn these particles at
		Vec3 rotatedVelocity = Vec3(
									initialVelocity_.x_ * cosf(randVelAngle * static_cast<float>(DEG_TO_RAD)) - 
														initialVelocity_.y_ * sinf(randVelAngle * static_cast<float>(DEG_TO_RAD)), 
									initialVelocity_.y_ * cosf(randVelAngle * static_cast<float>(DEG_TO_RAD)) + 
														initialVelocity_.x_ * sinf(randVelAngle * static_cast<float>(DEG_TO_RAD))
								);
		// TODO: Make the initial properties random
		// Source: https://stackoverflow.com/questions/686353/random-float-number-generation
		particle.lifeTime_ = particle.age_ = random_.RandomFloat(minLifeTime_, maxLifeTime_);
		particle.velocity_ = rotatedVelocity;
		particle.acceleration_ = startAcceleration_;
		particle.color_ = startColor_;
		particle.size_ = startSize_;
		particle.position_ = transform_->GetLocalTranslation();
		++numParticles_;
	}
}

// Public Member Functions

Junior::ParticleEmitter::ParticleEmitter()
	: particleSpawnTimer_(0.0f), maxLifeTime_(0), minLifeTime_(0), initialVelocity_(0, 0, 0), randomVelocityAngle_(0),
	  maxParticles_(0), numParticles_(0), particleSpawnCount_(0), particleSpawnWait_(0), loop_(false), particles_(),
	  startAcceleration_(0, 0, 0),
	  startSize_(20), endingSize_(50), colorInterpolate_(Lerp), sizeInterpolate_(Lerp), random_(), textureAtlas_(0)
{
}

Junior::ParticleEmitter::ParticleEmitter(const ParticleEmitter& other)
	: particleSpawnCount_(other.particleSpawnCount_), maxLifeTime_(other.maxLifeTime_), minLifeTime_(other.minLifeTime_),
	maxParticles_(other.maxParticles_), numParticles_(other.numParticles_), particleSpawnWait_(other.particleSpawnWait_),
	startSize_(other.startSize_), endingSize_(other.endingSize_), initialVelocity_(other.initialVelocity_),
	randomVelocityAngle_(0), particleSpawnTimer_(0.0f), loop_(other.loop_), random_(), textureAtlas_(0),
	startAcceleration_(other.startAcceleration_),
	particles_(), colorInterpolate_(other.colorInterpolate_), sizeInterpolate_(other.sizeInterpolate_)
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
	// Seed the random number generator
	random_.Seed(0);
	// Spawn particles
	SpawnParticles();
}

void Junior::ParticleEmitter::Update(double dt)
{
	// Check if we need to spawn any particles
	particleSpawnTimer_ += static_cast<float>(dt);
	if (particleSpawnTimer_ >= particleSpawnWait_ && loop_)
	{
		particleSpawnTimer_ -= particleSpawnWait_;
		// Start spawning particles
		SpawnParticles();
	}

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

			// Clear the current particle and swap it
			memset(&current, 0, sizeof(Particle));
			current = swappedParticle;
			swappedParticle = lastCurrent;
			// If the particle is dead, then swap this dead particle into the last live particle we have (at the end of the list)
			// Decrement the number of particles we have because we found one dead
			--numParticles_;
		}
		else
		{
			// Otherwise, update it and move on
			// Update the velocity
			current.velocity_ += current.acceleration_ * static_cast<float>(dt);
			// Update the current position
			current.position_ += current.velocity_ * static_cast<float>(dt);
			// Change the color of the particle
			current.color_ = colorInterpolate_(startColor_, endColor_, 1 - (current.age_ / current.lifeTime_));
			// Change the size of the particle
			current.size_ = sizeInterpolate_(startSize_, endingSize_, 1 - (current.age_ / current.lifeTime_));

			++particle;
		}
	}
}

void Junior::ParticleEmitter::Unload()
{
	particles_.clear();
}

void Junior::ParticleEmitter::Serialize(Parser& parser) const
{
	parser.WriteVariable("maxLifetime", maxLifeTime_);
	parser.WriteVariable("minLifetime", minLifeTime_);
	parser.WriteVariable("maxParticles", maxParticles_);
	parser.WriteVariable("particleSpawnCount", particleSpawnCount_);
	parser.WriteVariable("particleSpawnWait", particleSpawnWait_);
	parser.WriteVariable("startColor", startColor_);
	parser.WriteVariable("endColor", endColor_);
	parser.WriteVariable("startSize", startSize_);
	parser.WriteVariable("endingSize", endingSize_);
	parser.WriteVariable("initialVelocity", initialVelocity_);
	parser.WriteVariable("randomVelocityAngle", randomVelocityAngle_);
	parser.WriteVariable("startAcceleration", startAcceleration_);
	parser.WriteVariable("loop", loop_);
}

void Junior::ParticleEmitter::Deserialize(Parser& parser)
{
	parser.ReadVariable("maxLifetime", maxLifeTime_);
	parser.ReadVariable("minLifetime", minLifeTime_);
	parser.ReadVariable("maxParticles", maxParticles_);
	parser.ReadVariable("particleSpawnCount", particleSpawnCount_);
	parser.ReadVariable("particleSpawnWait", particleSpawnWait_);
	parser.ReadVariable("startColor", startColor_);
	parser.ReadVariable("endColor", endColor_);
	parser.ReadVariable("startSize", startSize_);
	parser.ReadVariable("endingSize", endingSize_);
	parser.ReadVariable("initialVelocity", initialVelocity_);
	parser.ReadVariable("randomVelocityAngle", randomVelocityAngle_);
	parser.ReadVariable("startAcceleration", startAcceleration_);
	parser.ReadVariable("loop", loop_);
}

std::vector<Junior::Particle>& Junior::ParticleEmitter::GetParticleList()
{
	return particles_;
}

unsigned Junior::ParticleEmitter::GetNumParticlesAlive() const
{
	return numParticles_;
}