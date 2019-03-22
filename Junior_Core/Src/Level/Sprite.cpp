/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File Name: Sprite.cpp
 * Description: Defines how Sprite works
 * Created: 13-Feb-2019
 * Last Modified: 14-Feb-2019
*/

// Includes
#include "Sprite.h"				// Sprite
#include "Graphics.h"			// Graphics
#include "TextureAtlas.h"		// Texture Atlas
#include "Texture.h"			// Texture
#include "RenderJob.h"			// Render Job
#include "GameObject.h"			// Game Object
#include "MemoryManager.h"		// Memory Manager
#include "Debug.h"				// Debug

#include <iostream>				// IO STREAM

// Public Member Functions
Junior::Sprite::Sprite()
	: Component("Sprite"), texture_(nullptr), job_(nullptr), atlasNode_(nullptr)
{
	texture_ = new Texture;
}

Junior::Sprite::Sprite(const std::string& path)
	: Component("Sprite"), texture_(nullptr), job_(nullptr), atlasNode_(nullptr)
{
	texture_ = new Texture;
	texture_->LoadFromDisk(path);
}

void Junior::Sprite::Initialize()
{
	// Debug printing
	Debug& debug = Debug::GetInstance();
	// Update the render job we are going to use
	job_ = owner_->GetRenderJob();
	if (texture_)
	{
		// Get the texture inside the texture atlas
		Graphics& graphics = Graphics::GetInstance();
		TextureAtlas* atlas = graphics.GetTextureAtlas();
		// Create the node to store inside the tree
		atlasNode_ = new AtlasNode(texture_->GetDimension(0), texture_->GetDimension(1));
		atlas->Push(&atlasNode_);
		atlas->UpdateNodePixels(atlasNode_, texture_->GetPixels());
		graphics.UpdateTextureAtlas();
		debug.Print<std::string>(debug.GetDebugLevelName(DebugLevel::NOTIFICATION));
		debug.PrintLn<std::string>("Finished adding data to sprite");
		// TODO: Update the sprite's texture coordinates
		// X offset, Y offset and uniform scale
		// Scale
		job_->uvTranslationAndScale_.z_ = static_cast<float>(atlasNode_->width_) / static_cast<float>(atlas->GetWidth()) - 0.01f;
		job_->uvTranslationAndScale_.w_ = static_cast<float>(atlasNode_->height_) / static_cast<float>(atlas->GetHeight()) - 0.01f;
		// Offset
		job_->uvTranslationAndScale_.x_ = static_cast<float>(atlasNode_->xPos_) / static_cast<float>(atlas->GetWidth()) + 0.005f;
		job_->uvTranslationAndScale_.y_ = static_cast<float>(atlasNode_->yPos_) / static_cast<float>(atlas->GetHeight()) + 0.005f;
	}
}

void Junior::Sprite::Update(double dt)
{
}

void Junior::Sprite::Clean(MemoryManager* manager)
{
	delete texture_;
}

void Junior::Sprite::SetUVModifications(float xOffset, float yOffset)
{
	TextureAtlas* atlas = Graphics::GetInstance().GetTextureAtlas();
	SetUVModifications(
		xOffset, 
		yOffset, 
		static_cast<float>(texture_->GetDimension(0)) / static_cast<float>(atlas->GetWidth()),
		static_cast<float>(texture_->GetDimension(1)) / static_cast<float>(atlas->GetHeight())
	);
}

void Junior::Sprite::SetUVModifications(float xOffset, float yOffset, float xScale, float yScale)
{
	job_->uvTranslationAndScale_.x_ = xOffset;
	job_->uvTranslationAndScale_.y_ = yOffset;
	job_->uvTranslationAndScale_.z_ = xScale;
	job_->uvTranslationAndScale_.w_ = yScale;
}

void Junior::Sprite::LoadFromDisk(const std::string& path)
{
	// We can only add a spot to the texture altas once, no more
	if (atlasNode_)
		return;

	texture_->LoadFromDisk(path);
	Graphics& graphics = Graphics::GetInstance();
	TextureAtlas* atlas = graphics.GetTextureAtlas();
	// Create the node to store inside the tree
	atlasNode_ = new AtlasNode(texture_->GetDimension(0), texture_->GetDimension(1));
	atlas->Push(&atlasNode_);
}

Junior::Texture* Junior::Sprite::GetTexture() const
{
	return texture_;
}

Junior::AtlasNode* Junior::Sprite::GetNode() const
{
	return atlasNode_;
}