/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File Name: Sprite.cpp
 * Description: Defines how Sprite works
 * Created: 13 Feb 2019
 * Last Modified: 4 May 2019
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
#include "ResourceManager.h"	// Resource Manager

// Public Member Functions
Junior::Sprite::Sprite()
	: Component(), path_(), texture_(nullptr), atlasNode_(nullptr), atlas_(nullptr)
{
}

Junior::Sprite::Sprite(const std::string& path)
	: Component(), path_(path), texture_(nullptr), atlasNode_(nullptr), atlas_(nullptr)
{
	texture_ = ResourceManager::GetInstance().GetResource<Texture>("path");
}

void Junior::Sprite::Initialize()
{
	// Debug printing
	Debug& debug = Debug::GetInstance();
	if (texture_)
	{
		// Get the texture inside the texture atlas
		Graphics& graphics = Graphics::GetInstance();
		atlas_ = graphics.GetTextureAtlas();
		// Create the node to store inside the tree
		const std::string& textureDir = texture_->GetResourceDir();
		atlasNode_ = atlas_->Find(textureDir);
		// If we found the node, then we skip creating the node
		if (!atlasNode_)
		{
			// Otherwise, we need to create it
			atlasNode_ = new AtlasNode(texture_->GetDimension(0), texture_->GetDimension(1), textureDir);
			atlas_->Push(&atlasNode_);
			atlas_->UpdateNodePixels(atlasNode_, texture_->GetPixels());
			graphics.UpdateTextureAtlas();
		}
		// X offset, Y offset and uniform scale
		atlasScale_.x_ = static_cast<float>(atlasNode_->width_) / static_cast<float>(atlas_->GetWidth());
		atlasScale_.y_ = static_cast<float>(atlasNode_->height_) / static_cast<float>(atlas_->GetHeight());
		atlasOffset_.x_ = static_cast<float>(atlasNode_->xPos_) / static_cast<float>(atlas_->GetWidth());
		atlasOffset_.y_ = static_cast<float>(atlasNode_->yPos_) / static_cast<float>(atlas_->GetHeight());
	}
}

Junior::Sprite::Sprite(const Sprite& sprite)
	: Component("Sprite"), path_(sprite.path_), atlasNode_(nullptr)
{
	if (path_ != "")
	{
		texture_ = ResourceManager::GetInstance().GetResource<Texture>(path_);
	}
}

void Junior::Sprite::Update(double dt)
{
}

void Junior::Sprite::Unload()
{
	delete texture_;
}

void Junior::Sprite::SetUVModifications(float xOffset, float yOffset)
{
	SetUVModifications(
		xOffset, 
		yOffset, 
		static_cast<float>(texture_->GetDimension(0)) / static_cast<float>(atlas_->GetWidth()),
		static_cast<float>(texture_->GetDimension(1)) / static_cast<float>(atlas_->GetHeight())
	);
}

void Junior::Sprite::SetUVModifications(float xOffset, float yOffset, float xScale, float yScale)
{
	atlasScale_ = Vec3(xScale, yScale);
	atlasOffset_ = Vec3(xOffset, yOffset);
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

const Junior::Vec3& Junior::Sprite::GetAtlasOffset() const
{
	return atlasOffset_;
}

const Junior::Vec3& Junior::Sprite::GetAtlasScale() const
{
	return atlasScale_;
}

unsigned Junior::Sprite::GetAtlasID() const
{
	return atlas_->GetID();
}

void Junior::Sprite::Serialize(Parser& parser) const
{
	// Only serialize the path to the texture
	parser.WriteVariable("texturePath", path_);
}

void Junior::Sprite::Deserialize(Parser& parser)
{
	// Deserialize the path to the texture and load the sprite's texture
	delete texture_;
	parser.ReadVariable("texturePath", path_);
	texture_ = ResourceManager::GetInstance().GetResource<Texture>(path_);
}