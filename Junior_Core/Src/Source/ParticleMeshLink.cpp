/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: ParticleMeshLink.cpp
 * Description: The mesh link used to send rendering data to the particle mesh
 * Created: 10 May 2019
 * Last Modified: 10 May 2019
*/

// Incldudes
#include "ParticleMeshLink.h"
#include "GameObject.h"				// Game Object
#include "Graphics.h"				// Graphics
#include "ParticleMesh.h"			// Particle Mesh
#include "ParticleEmitter.h"		// Particle Emitter
#include "Sprite.h"					// Sprite

// Public Member Functions

Junior::ParticleMeshLink::ParticleMeshLink()
	: emitter_(nullptr), shaderDir_("..//Assets//Shaders//particle")
{
}

Junior::ParticleMeshLink::ParticleMeshLink(const ParticleMeshLink& other)
	: emitter_(nullptr), shaderDir_("..//Assets//Shaders//particle")
{
}

void Junior::ParticleMeshLink::Initialize()
{
	if (owner_)
	{
		// Get the game object's particle emitter
		emitter_ = owner_->GetComponent<ParticleEmitter>();
		// Get the game object's sprite
		sprite_ = owner_->GetComponent<Sprite>();
		// Send the data to the Particle Mesh
		ParticleMesh* particleMesh = Graphics::GetInstance().GetMesh<ParticleMesh>(shaderDir_);
		particleMesh->AddList(emitter_);
	}
}

void Junior::ParticleMeshLink::Update(double dt)
{
	// Update all of the particle's uv and scale
	std::vector<Particle>& particles = emitter_->GetParticleList();
	for (auto iter = particles.begin(); iter != particles.end(); ++iter)
	{
		// If we hit a dead particle, the rest of them from this point on are dead so ignore the rest
		if (iter->age_ <= 0.0f)
			break;
		// Otherwise, update the scale and other things
		Vec3 atlasOffset = sprite_->GetAtlasOffset();
		Vec3 atlasScale = sprite_->GetAtlasScale();
		iter->uvTranslationAndScale_.x_ = atlasOffset.x_;
		iter->uvTranslationAndScale_.y_ = atlasOffset.y_;
		iter->uvTranslationAndScale_.z_ = atlasScale.x_;
		iter->uvTranslationAndScale_.w_ = atlasScale.y_;
	}
}

void Junior::ParticleMeshLink::Unload()
{
}