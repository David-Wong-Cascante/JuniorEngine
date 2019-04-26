/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: Animator.h
 * Description: Defines how the animator is going to work
 * Created: 14 Feb 2019
 * Last Modified: 26 Apr 2019
*/

// Includes
#include "Animator.h"			// Animator
#include "GameObject.h"			// Game Object
#include "Sprite.h"				// Sprite
#include "Graphics.h"			// Graphics
#include "TextureAtlas.h"		// Texture Atlas
#include "Texture.h"			// Texture
#include "Parser.h"				// Parser

// Public Member Functions
Junior::Animator::Animator(unsigned columns, unsigned rows)
	: Component(), currentFrame_(0), playing_(false), loop_(false), start_(0), end_(0), 
	numColumns_(columns), numRows_(rows), timer_(0.0), timePerFrame_(0.0), sprite_(nullptr),
	startXOffset_(0), startYOffset_(0), textureXSize_(0), textureYSize_(0), columnSize_(0),
	rowSize_(0)
{
}

Junior::Animator::Animator(const Animator& other)
	: Component(), currentFrame_(other.currentFrame_), playing_(other.playing_), loop_(other.loop_), start_(other.start_),
	end_(other.end_), numColumns_(other.numColumns_), numRows_(other.numRows_), timer_(other.timer_), timePerFrame_(other.timePerFrame_),
	startXOffset_(0), startYOffset_(0), textureXSize_(other.textureXSize_),
	textureYSize_(other.textureYSize_), columnSize_(other.columnSize_), rowSize_(other.rowSize_)
{
	
}

void Junior::Animator::Initialize()
{
	// Get the sprite component
	sprite_ = owner_->GetComponent<Sprite>();
	//sprite_ = static_cast<Sprite*>(owner_->GetComponent("Sprite"));
	AtlasNode* node = sprite_->GetNode();
	// Get the atlas
	Graphics& graphics = Graphics::GetInstance();
	TextureAtlas* atlas = graphics.GetTextureAtlas();
	// Set the offsets
	startXOffset_ = static_cast<float>(node->xPos_) / static_cast<float>(atlas->GetWidth());
	startYOffset_ = static_cast<float>(node->yPos_) / static_cast<float>(atlas->GetHeight());
	// Set the row and column size
	Texture* texture = sprite_->GetTexture();
	textureXSize_ = static_cast<float>(node->width_) / static_cast<float>(atlas->GetWidth());
	textureYSize_ = static_cast<float>(node->height_) / static_cast<float>(atlas->GetHeight());
	columnSize_ = textureXSize_ / static_cast<float>(numColumns_);
	rowSize_ = textureYSize_ / static_cast<float>(numRows_);
	// Start rendering the first frame
	SetFrame(currentFrame_);
}

void Junior::Animator::Update(double dt)
{
	if (playing_)
	{
		// Increase the timer
		timer_ += dt;
		if (timer_ >= timePerFrame_)
		{
			// When the time is up switch frames
			timer_ -= timePerFrame_;
			++currentFrame_;
			if (currentFrame_ > end_)
			{
				if (loop_)
				{
					currentFrame_ = start_;
				}
				else
				{
					playing_ = false;
				}
			}
		}
	}

	// Change the frame to the correct animation
	SetFrame(currentFrame_);
}

void Junior::Animator::Unload()
{
}

void Junior::Animator::Play(unsigned start, unsigned end, double timePerFrame, bool looping)
{
	start_ = start;
	timePerFrame_ = timePerFrame;
	currentFrame_ = start;
	end_ = end;
	loop_ = looping;
	playing_ = true;
	timer_ = 0.0;
}

void Junior::Animator::Stop()
{
	playing_ = false;
}

void Junior::Animator::SetFrame(unsigned frame)
{
	float u = startXOffset_ + columnSize_ * static_cast<float>((frame % numColumns_));
	float v = startYOffset_ + textureYSize_ - rowSize_ * (1 + (frame / numColumns_));
	sprite_->SetUVModifications(u, v, columnSize_, rowSize_);
}

bool Junior::Animator::IsPlaying() const
{
	return playing_;
}

void Junior::Animator::Serialize(Parser& parser) const
{
	parser.WriteVariable("currentFrame", currentFrame_);
	parser.WriteVariable("playing", playing_);
	parser.WriteVariable("loop", loop_);
	parser.WriteVariable("animStart", start_);
	parser.WriteVariable("animEnd", end_);
	parser.WriteVariable("numColumns", numColumns_);
	parser.WriteVariable("numRows", numRows_);
	parser.WriteVariable("timePerFrame", timePerFrame_);
}

void Junior::Animator::Deserialize(Parser& parser)
{
	parser.ReadVariable("currentFrame", currentFrame_);
	parser.ReadVariable("playing", playing_);
	parser.ReadVariable("loop", loop_);
	parser.ReadVariable("animStart", start_);
	parser.ReadVariable("animEnd", end_);
	parser.ReadVariable("numColumns", numColumns_);
	parser.ReadVariable("numRows", numRows_);
	parser.ReadVariable("timePerFrame", timePerFrame_);
}