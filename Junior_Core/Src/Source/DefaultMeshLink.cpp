/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: DefaultMeshLink.cpp
* Description: Links this game object to the DefaultMesh to render it on screen
* Created: 4 May 2018
* Last Modified: 4 May 2019
*/

// Includes
#include "DefaultMeshLink.h"
#include "DefaultMesh.h"		// Default Mesh
#include "Graphics.h"			// Graphics
#include "GameObject.h"			// Game Object
#include "Transform.h"			// Transform
#include "Sprite.h"				// Sprite

// Public Member Functions

Junior::DefaultMeshLink::DefaultMeshLink(bool loadMeshData)
	: defaultProgramDir("..//Assets//Shaders//starter"), renderJob_(nullptr), sprite_(nullptr)
{
	// Get a new render job
	if (loadMeshData)
	{
		Graphics& graphics = Graphics::GetInstance();
		renderJob_ = graphics.GetMesh<DefaultMesh>(defaultProgramDir)->GetNewRenderJob();
	}
}

Junior::DefaultMeshLink::DefaultMeshLink(const DefaultMeshLink& other)
	: defaultProgramDir("..//Assets//Shaders//starter"), renderJob_(nullptr), transform_(nullptr), sprite_(nullptr)
{
	// Get a new render job
	Graphics& graphics = Graphics::GetInstance();
	renderJob_ = graphics.GetMesh<DefaultMesh>(defaultProgramDir)->GetNewRenderJob();
}

void Junior::DefaultMeshLink::Initialize()
{
	// Get all the necessary components
	transform_ = owner_->GetComponent<Transform>();
	sprite_ = owner_->GetComponent<Sprite>();
}

void Junior::DefaultMeshLink::Update(double)
{
	// Update the transform if it exists
	if (transform_)
	{
		renderJob_->transformation_ = transform_->GetGlobalTransformation();
	}
	// Update the sprite if it exists
	if (sprite_)
	{
		Vec3 atlasOffset = sprite_->GetAtlasOffset();
		Vec3 atlasScale = sprite_->GetAtlasScale();
		renderJob_->uvTranslationAndScale_ = Vec3(atlasOffset.x_, atlasOffset.y_, atlasScale.x_, atlasScale.y_);
	}
}

void Junior::DefaultMeshLink::Unload()
{
	if (renderJob_)
	{
		Graphics& graphics = Graphics::GetInstance();
		graphics.GetMesh<DefaultMesh>(defaultProgramDir)->RemoveRenderJob(renderJob_);
		delete renderJob_;
	}
}