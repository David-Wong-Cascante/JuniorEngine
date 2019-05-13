#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: ParticleEmitter.h
* Description: Emits the particles
* Created: 6 May 2018
* Last Modified: 6 May 2019
*/

// Includes
#include <vector>					// Vector
#include "Component.h"				// Component
#include "Particle.h"				// Particle
#include "Random.h"					// Random

namespace Junior
{
	// Typedef For Linear Interpolation
	// Params:
	//	start: The starting value of the property
	//	end: The ending value of the property
	//	t: A value from [0, 1] that blends the property
	typedef Vec3 (*InterpolateVec3Ptr)(const Vec3& start, const Vec3& end, float t);
	// Params:
	//	start: The starting value of the property
	//	end: The ending value of the property
	//	t: A value from [0, 1] that blends the property
	typedef float(*InterpolateFloatPtr)(const float& start, const float& end, float t);

	// Forward Declarations
	class Transform;

	// Global Functions

	// Linearly interpolates between two values
	// Params:
	//	start: The start of the linear interpolation
	//	end: The end of the linear interpolation
	// Returns: A value between the start and end at point t
	Vec3 Lerp(const Vec3& start, const Vec3& end, float t);
	// Linearly interpolates between two values
	// Params:
	//	start: The start of the linear interpolation
	//	end: The end of the linear interpolation
	// Returns: A value between the start and end at point t
	float Lerp(const float& start, const float& end, float t);

	// ParticleEmitter
	class ParticleEmitter : public Component<ParticleEmitter>
	{
	private:
		// Private Member Variables

		// The particles we have
		std::vector<Particle> particles_;
		// The timer that keeps track of when to spawn the particles
		float particleSpawnTimer_;
		// The number of particles that are currently alive
		unsigned numParticles_;
		// RNG
		Random random_;

		// Private Member Functions

		// Spawns the particles in a burst
		void SpawnParticles();

	public:
		// Private Member Variables

		// The transform of the object emitting the particles
		Transform* transform_;
		// The function pointer for interpolating each particle's color
		InterpolateVec3Ptr colorInterpolate_;
		// The function pointer for interpolating each particle's size
		InterpolateFloatPtr sizeInterpolate_;
		// The starting color of the particles
		Vec3 startColor_;
		// The ending color of the particles
		Vec3 endColor_;
		// The starting size of the particles
		float startSize_;
		// The ending size of the particles
		float endingSize_;
		// The maximum amount of particles we can have
		unsigned maxParticles_;
		// How many particles we spawn per burst
		unsigned particleSpawnCount_;
		// The max lifetime
		float maxLifeTime_;
		// The min lifetime
		float minLifeTime_;
		// How long we wait before spawning particles_;
		float particleSpawnWait_;
		// Whether the emitter loops
		bool loop_;
		// The texture atlas we are using
		unsigned textureAtlas_;

		// Public Member Functions

		// Constructor
		// Params:
		ParticleEmitter();
		// Copy Constructor
		// Params:
		//	other: The other particle emitter we are copying from
		ParticleEmitter(const ParticleEmitter& other);
		// Initialize the emitter
		void Initialize() override;
		// Update the emitter and all the particles with it
		// Params:
		//	dt: The delta time between frames
		void Update(double dt) override;
		// Unloads the component
		void Unload() override;
		// Writes this particle emitter to a file
		// Params:
		//	parser: The parser we are using to write to the file
		void Serialize(Parser& parser) const override;
		// Reads this particle emitter from a file
		// Params:
		//	parser: The parser we are using to read this file
		void Deserialize(Parser& parser) override;
		// Returns: The list of particles in this system
		std::vector<Particle>& GetParticleList();
		// Returns: The number of particles alive in the system
		unsigned GetNumParticlesAlive() const;
	};
}