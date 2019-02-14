/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: TextureAtlasTree.cpp
 * Description: Shows how TextureAtlasMap works
 * Created: 12-Feb-2019
 * Last Modified: 14-Feb-2019
*/

// Includes
#include "TextureAtlas.h"
#include <iostream>					// IO Stream
#include "OpenGLBundle.h"			// OpenGL Stuff


// Public Member Functions

// Atlas Node
Junior::AtlasNode::AtlasNode(int width, int height)
	: parent_(nullptr), children_{ nullptr, nullptr }, used_(false), offset_(nullptr), width_(width), height_(height), xPos_(0), yPos_(0)
{
}

void Junior::PrintNode(std::ostream& stream, const AtlasNode* node, unsigned tabCounter)
{
	if (!node)
		return;

	for (unsigned i = 0; i < tabCounter * 3; ++i)
		stream << " ";

	stream
		<< "-> Node: (Width: "
		<< node->width_
		<< ", Height: "
		<< node->height_
		<< ", XPos: "
		<< node->xPos_
		<< ", YPos: "
		<< node->yPos_
		<< ", Used: "
		<< node->used_
		<< ")";
	
	// Recurse through the node's children
	++tabCounter;
	if (node->children_[0])
	{
		stream << std::endl;
		PrintNode(stream, node->children_[0], tabCounter);
	}
	
	if (node->children_[1])
	{
		stream << std::endl;
		PrintNode(stream, node->children_[1], tabCounter);
	}
}

// Texture Atlas Map

// Private Member Functions
void Junior::TextureAtlas::CopyNode(Junior::AtlasNode* node, Junior::AtlasNode* copy)
{
	// Copy over the data into copy
	copy->width_ = node->width_;
	copy->height_ = node->height_;
	copy->xPos_ = node->xPos_;
	copy->yPos_ = node->yPos_;
	copy->offset_ = node->offset_;
	copy->parent_ = node->parent_;

	// If it has children, then recurse over its children
	if (node->children_[0])
	{
		copy->children_[0] = new AtlasNode(0, 0);
		CopyNode(node->children_[0], copy->children_[0]);
	}

	if (node->children_[1])
	{
		copy->children_[1] = new AtlasNode(0, 0);
		CopyNode(node->children_[1], copy->children_[1]);
	}
}

void Junior::TextureAtlas::CopyTree(Junior::AtlasNode* tree, Junior::AtlasNode** copy)
{
	*copy = new AtlasNode(0, 0);
	CopyNode(tree, *copy);
}

inline void Junior::TextureAtlas::SetOffset(Junior::AtlasNode* node)
{
	node->offset_ = pixels_ + totalWidth_ * node->yPos_ + node->xPos_;
}

// Public Member Functions
Junior::TextureAtlas::TextureAtlas(int width, int height, int numChannels)
	: pixels_(nullptr), head_(nullptr), totalWidth_(width), totalHeight_(height), numChannels_(numChannels)
{
	// Make the texture array
	pixels_ = new unsigned char[width * height * numChannels];
	head_ = new AtlasNode(width, height);
	mapChildren_.push_back(head_);
}

Junior::TextureAtlas::TextureAtlas(const TextureAtlas& other)
{
	// Copy over the elements of other into this one
	// Copying is super slow because we got to copy a tree over
	totalWidth_ = other.totalWidth_;
	totalHeight_ = other.totalHeight_;
	numChannels_ = other.numChannels_;
	unsigned size = totalWidth_ * totalHeight_ * numChannels_;
	pixels_ = new unsigned char[size];
	for (unsigned i = 0; i < size; ++i)
	{
		pixels_[i] = other.pixels_[i];
	}

	CopyTree(other.head_, &head_);
}


Junior::TextureAtlas::TextureAtlas(int numChannels)
	: pixels_(nullptr), head_(nullptr), numChannels_(numChannels), mapChildren_()
{
	// Find the largest possible size to put into a texture array
	// Keep in mind the texture will be square regardless
	int getterWidth;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &getterWidth);
	totalHeight_ = totalWidth_ = static_cast<unsigned>(getterWidth);
	// Make the texture array
	pixels_ = new unsigned char[totalWidth_ * totalHeight_ * numChannels_];
	head_ = new AtlasNode(totalWidth_, totalHeight_);
	mapChildren_.push_back(head_);
}

Junior::TextureAtlas& Junior::TextureAtlas::operator=(const TextureAtlas& other)
{
	if (this == &other)
		return *this;

	// Delete things from this
	Reset(head_);
	mapChildren_.clear();
	delete head_;
	delete[] pixels_;

	// Copy over the elements of other into this one
	// Copying is super slow because we got to copy a tree over
	totalWidth_ = other.totalWidth_;
	totalHeight_ = other.totalHeight_;
	unsigned size = totalWidth_ * totalHeight_;
	pixels_ = new unsigned char[size];
	for (unsigned i = 0; i < size; ++i)
	{
		pixels_[i] = other.pixels_[i];
	}

	CopyTree(other.head_, &head_);

	return *this;
}

Junior::TextureAtlas::~TextureAtlas()
{
	// Clear the tree
	Reset(head_);
	mapChildren_.clear();
	delete[] pixels_;
}

void Junior::TextureAtlas::Push(AtlasNode** node, AtlasNode* plot)
{
#ifdef _DEBUG
	std::cout << "[NOTIFICATION]: Pushing node size [" << (*node)->width_ << ", " << (*node)->height_ << "]" << std::endl;
#endif
	// Quit out of the function early if we tried to set data into an already used plot
	if (plot->used_)
	{
#ifdef _DEBUG
		std::cout << "[ERROR]: Attempted to push a node into a used plot:" << std::endl;
#endif
		PrintNode(std::cout, plot);
		std::cout << "!" << std::endl;
	}
	// Establish the two splits
	AtlasNode* firstSplit = nullptr;
	AtlasNode* secondSplit = nullptr;
	bool doneSplitting = false;
	// If the plot and node have the same width and height, then just use the plot
	if ((*node)->width_ == plot->width_ && (*node)->height_ == plot->height_)
	{
		// Copy over the data from plot to node
		delete *node;
		(*node) = plot;
		doneSplitting = true;
		// Marked as used
		(*node)->used_ = true;
	}

	// Do the first split with the big plot through the vertical split
	// Check whether the height of the node is smaller than that of the plot
	// if so, subidivide
	if (!doneSplitting)
	{
		if ((*node)->height_ < plot->height_)
		{
			// Split the main plot into two subsections which will become its children
			firstSplit = new AtlasNode(plot->width_, (*node)->height_);
			secondSplit = new AtlasNode(plot->width_, plot->height_ - (*node)->height_);
			// Set the correct x and y coordinates of the splits
			firstSplit->xPos_ = plot->xPos_;
			firstSplit->yPos_ = plot->yPos_;
			secondSplit->xPos_ = plot->xPos_;
			secondSplit->yPos_ = plot->yPos_ + firstSplit->height_;
			// Set the correct offsets of the subplots
			SetOffset(firstSplit);
			SetOffset(secondSplit);
			// Set the two splits as the plot's children
			plot->children_[0] = firstSplit;
			plot->children_[1] = secondSplit;
			firstSplit->parent_ = plot;
			secondSplit->parent_ = plot;
			// Add the first split to the childrenMap array
			mapChildren_.push_back(firstSplit);
			mapChildren_.push_back(secondSplit);
			// Marked as used
			plot->used_ = true;
			firstSplit->used_ = true;
		}
		// Only split the plot into two pieces if the plot heights are the same
		else if ((*node)->height_ == plot->height_)
		{
			doneSplitting = true;
			// Split the main plot into two subsections which will become its children
			firstSplit = new AtlasNode(plot->width_ - (*node)->width_, (*node)->height_);
			// The node's width and height should already be set
			// Set the correct x and y coordinates of the splits
			(*node)->xPos_ = plot->xPos_;
			(*node)->yPos_ = plot->yPos_;
			firstSplit->xPos_ = plot->xPos_ + (*node)->width_;
			firstSplit->yPos_ = plot->yPos_;
			// Set the correct offsets of the subplots
			SetOffset(firstSplit);
			SetOffset(*node);
			// Set the two splits as the plot's children
			plot->children_[0] = firstSplit;
			plot->children_[1] = *node;
			firstSplit->parent_ = plot;
			(*node)->parent_ = plot;
			// Add the first split to the childrenMap array
			mapChildren_.push_back(firstSplit);
			mapChildren_.push_back(*node);
			// Marked as used
			plot->used_ = true;
			(*node)->used_ = true;
		}
		else
		{
#if _DEBUG
			std::cout << "[WARNING]: Attempted to make a bigger subplot than its plot on the height (" << (*node)->height_ << " > " << plot->height_ << ")!" << std::endl;
#endif
		}
	}

	// Use the first subdivision as the host of the sub division, if it exists
	// Otherwise use the original plot
	if (!doneSplitting)
	{
		if (!firstSplit)
			firstSplit = plot;

		// Subdivide if the width of the subplot isn't bigger than that of the plot
		if ((*node)->width_ < firstSplit->width_)
		{
			// Use the plot pointer to finally fill it with data
			secondSplit = new AtlasNode(firstSplit->width_ - (*node)->width_, firstSplit->height_);
			// And the plot's data should already be set...
			// Set the offset coordiantes
			(*node)->xPos_ = firstSplit->xPos_;
			(*node)->yPos_ = firstSplit->yPos_;
			secondSplit->xPos_ = firstSplit->xPos_ + (*node)->width_;
			secondSplit->yPos_ = firstSplit->yPos_;
			// Set the offset
			SetOffset(*node);
			SetOffset(secondSplit);
			// Set the children of firstSplit
			firstSplit->children_[0] = *node;
			firstSplit->children_[1] = secondSplit;
			(*node)->parent_ = firstSplit;
			secondSplit->parent_ = firstSplit;
			// Add the node to the map children
			mapChildren_.push_back(*node);
			mapChildren_.push_back(secondSplit);
			firstSplit->used_ = true;
			(*node)->used_ = true;
			secondSplit->used_ = false;
		}
		else
		{
#ifdef _DEBUG
			std::cout << "[WARNING]: Attempted to make a bigger subplot than its plot on the width (" << (*node)->width_ << " > " << plot->width_ << ")!" << std::endl;
#endif
		}
	}

	// Remove all plots with children on them
	auto end = mapChildren_.end();
	auto begin = mapChildren_.begin();
	while(begin < end)
	{
		if ((*begin)->used_)
		{
			begin = mapChildren_.erase(begin);
			end = mapChildren_.end();
		}
		else
		{
			++begin;
		}
	}

#ifdef _DEBUG
	std::cout << "[NOTIFICATION]: Finished pushing node" << std::endl;
#endif
}

void Junior::TextureAtlas::Push(AtlasNode** node)
{
	// Only push the node when it exists
	if (!(*node))
		return;
	// Search through the entire child list to find the smallest plot that will fit this node
	auto begin = mapChildren_.begin();
	auto end = mapChildren_.end();
	AtlasNode* selected = nullptr;
	// Check for the node fits into the head
	if (!head_->used_ && (*node)->width_ <= (head_)->width_ && (*node)->height_ <= (head_)->height_)
	{
		// If so, select it
		selected = head_;
	}
	for (; begin < end; ++begin)
	{
		// See if the width and height are bigger than the node we are going too fit in
		if (!(*begin)->used_ && (*node)->width_ <= (*begin)->width_ && (*node)->height_ <= (*begin)->height_)
		{
			// Then, see if the width and height of *begin is smaller than the current select
			// if not, then set selected to *begin
			if (selected)
			{
				if (selected->width_ >= (*begin)->width_ && selected->height_ >= (*begin)->height_)
				{
					selected = *begin;
				}
			}
			else
			{
				selected = *begin;
			}
		}
	}

	// We found the smallest plot to fit the node in, so set it on that plot
	if (selected)
		Push(node, selected);
	else
	{
		delete *node;
		(*node) = nullptr;
	}
		
}

void Junior::TextureAtlas::Reset(AtlasNode* node)
{
	if (node)
	{
		for (unsigned i = 0; i < 2; ++i)
		{
			if (node->children_[i]) 
			{
				Reset(node->children_[i]);
				node->children_[i] = nullptr;
			}
		}
	}
	
	delete node;
}

void Junior::TextureAtlas::Reset()
{
	Reset(head_);
}

void Junior::TextureAtlas::UpdateNodePixels(AtlasNode* node, const unsigned char* outPixels)
{
	if (!node)
		return;
	// Use the offset inside node to painstakingly update the pixels of the tree in a contained square
	// The current pixel from outPixels
	unsigned currentPixel = 0;
	// Try drawing a square onto the texture with the correct width and height and position
	for (unsigned y = 0; y < node->height_; ++y)
	{
		for (unsigned x = 0; x < node->width_; ++x)
		{
			// Set the correct offset for the pixels we are about to draw
			if (x < totalWidth_ && x >= 0 && y < totalHeight_ && y >= 0)
			{
				unsigned offset = 4 * (node->xPos_ + x + totalWidth_ * (node->yPos_ + y));
				pixels_[offset + 0] = outPixels[currentPixel++];
				pixels_[offset + 1] = outPixels[currentPixel++];
				pixels_[offset + 2] = outPixels[currentPixel++];
				pixels_[offset + 3] = outPixels[currentPixel++];
			}
		}
	}
}

void Junior::TextureAtlas::UpdatePixels(const unsigned char* pixels)
{
	unsigned totalSize = totalWidth_ * totalHeight_;
	for (unsigned i = 0; i < totalSize * 4; ++i)
	{
		pixels_[i] = pixels[i];
	}
}

unsigned char* Junior::TextureAtlas::GetPixels() const
{
	return pixels_;
}

unsigned Junior::TextureAtlas::GetWidth() const
{
	return totalWidth_;
}

unsigned Junior::TextureAtlas::GetHeight() const
{
	return totalHeight_;
}

std::ostream& Junior::operator<<(std::ostream& stream, const TextureAtlas& atlas)
{
	PrintNode(stream, atlas.head_);
	return stream;
}