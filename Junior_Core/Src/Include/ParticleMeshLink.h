#pragma once
/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: ParticleMeshLink.h
 * Description: The mesh link used to send rendering data to the particle mesh
 * Created: 10 May 2019
 * Last Modified: 10 May 2019
*/

// Includes
#include <vector>				// std::vector
#include <string>				// std::string
#include "Component.h"			// Component

namespace Junior
{
	// Forward Declarations
	class ParticleEmitter;		// The particle emitter component this game object has
	class Sprite;				// The sprite this game object has

	class ParticleMeshLink : public Component<ParticleMeshLink>
	{
	private:
		// Private Constant Variables

		// The directory to the shader
		const std::string shaderDir_;

		// Private Member Variables

		// The particle emitter this class has
		ParticleEmitter* emitter_;
		// This object's sprite
		Sprite* sprite_;
		
	public:
		// Public Member Functions

		// Constructor
		ParticleMeshLink();
		// Copy Constructor
		// Params:
		//	other: The othehr particle mesh we are copying from
		ParticleMeshLink(const ParticleMeshLink& other);
		// Initializes the component
		void Initialize();
		// Updates the component
		// Params:
		//	dt: The delta time between the rendered frames
		void Update(double dt);
		// Unloads the component
		void Unload();
	};
}