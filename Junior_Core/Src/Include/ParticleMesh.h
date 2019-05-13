#pragma once
/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: ParticleMesh.h
 * Description: The mesh we are using to render the particles
 * Created: 10 May 2019
 * Last Modified: 10 May 2019
*/

// Includes
#include "Mesh.h"		// Mesh
#include "Particle.h"	// Particle

namespace Junior
{
	// Forward Declarations
	class ParticleEmitter;

	class ParticleMesh : public Mesh
	{
	private:
		// Private Member Constants

		// The number of attributes ParticleMesh has
		const unsigned numParticleAttribs_;

		// Private Member Variables

		// The list of particles we want to render
		std::vector<ParticleEmitter*> emitterParticleList_;
		// The buffer for all the particle data
		unsigned particleBuffer_;
	
	public:
		// Public Member Functions

		// Constructor
		ParticleMesh();
		// Virtual Destructor
		~ParticleMesh() override;
		// Draws the mesh into graphics
		// Params:
		//	shaderID: The shader id we are using to render
		void Draw(unsigned shaderID) override;
		// Adds a list to the emitter list
		// Params:
		//	emitterList: The particles we want to add to this list
		void AddList(ParticleEmitter* emitterList);
	};
}