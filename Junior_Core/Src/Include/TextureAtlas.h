#pragma once
/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: TextureAtlasTree.h
 * Description: Declares the texture atlas' functionality
 * Created: 12 Feb 2019
 * Last Modified: 13 May 2019
*/

// Defines
#define NUM_NODE_CHILDREN 2

// Includes
#include <vector>
#include <string>

namespace Junior
{
	struct AtlasNode
	{
		// Whether the node is being used or not
		bool used_ = false;
		// The offset to start drawing the pixels
		unsigned char* offset_;
		// The width of the node in pixels
		unsigned width_;
		// The height of the node in pixels
		unsigned height_;
		// The x-coordinate of the top left corner of the plot
		unsigned xPos_;
		// The y-coordinates of the top left corner of the plot
		unsigned yPos_;
		// The parent of the node (if null, then this node is the head of the tree)
		AtlasNode* parent_;
		// The children of this AtlasNode
		AtlasNode* children_[2];
		// The name of the node
		std::string nodeName_;
		
		// Constructs a pre-push node
		// Params:
		//	width: The width of the node
		//	height: The height of the node
		AtlasNode(int width, int height, const std::string& name = "");
	};

	class TextureAtlas
	{
	private:
		// Private Member Variables

		// The original pixels of the texture map
		unsigned char* pixels_;
		// The head of the texture map
		AtlasNode* head_;
		// Total Width
		unsigned totalWidth_;
		// Total Height
		unsigned totalHeight_;
		// The number of channels we have
		unsigned numChannels_;
		// The ID of the texture atlas
		unsigned id_;
		// The vector of the map's children
		std::vector<AtlasNode*> mapChildren_;

		// Private Member Functions

		// Recursively copies over a tree to this atlas' tree
		// Params:
		//	node: The node we are copying from (starting with the head)
		//	copy: The node meant to be a copy of 'node' (starting with the head)
		//	tree: The tree that its nodes are being copied to
		void CopyNode(AtlasNode* node, AtlasNode* copy);
		// Copies a tree over to another
		// Params:
		//	tree: The original tree
		//	copy: The copy of the original tree
		void CopyTree(AtlasNode* tree, AtlasNode** copy);
		// Set the correct offset to the node in relation to this map
		// Params:
		//	node: The node we want to set the data to
		//	xPos: The x position of top left corner of the plot
		//	yPos: The y position of the top left corner of the plot
		inline void SetOffset(AtlasNode* node);
		// Finds the first node with the same name recursively
		// Params:
		//	node: The node we are currently checkinng
		//	name: The name we are checking for
		AtlasNode* FindNode(AtlasNode* node, const std::string& name) const;
	public:
		// Public Member Functions
		// Constructs a ready texture map
		// Params:
		//	width: The max width of the map
		//	height: The max height of the map
		//	numChannels: The number of channels this texture has
		//	id: The texture atlas' id in the shader array
		TextureAtlas(int width, int height, int numChannels, unsigned id);
		// Oops, forgot the copy constructor
		//  Params:
		//	other: The other texture atlas we are trying to copy from
		TextureAtlas(const TextureAtlas& other);
		// Constructs a ready texture map with the largest size possible specified by OpenGL
		// Params:
		//	numChannels = The number of channels this atlas has
		TextureAtlas(int numChannels = 4);
		// Deconstructs and deletes the map's nodes
		~TextureAtlas();
		// Safely assigns one texture map onto another
		// Params:
		//	other: The atlas we want to copy from
		// Returns: The copy of the atlas map
		TextureAtlas& operator=(const TextureAtlas& other);
		// Pushes the new node onto a selected child of the tree
		// Params:
		//	node: The child to be pushed into the tree
		//	chosenPlot: The plot to push the child into
		void Push(AtlasNode** node, AtlasNode* chosenPlot);
		// Pushes the new node onto the tree
		// Params:
		//	node: The child to be pushed into the tree
		void Push(AtlasNode** node);
		// Attempts to find a node with the same name
		// Params:
		//	name: The name of the node
		AtlasNode* Find(const std::string& name) const;
		// Resets a node (clears all of its children)
		// Params:
		//	node: The node we are going to use for recursion
		void Reset(AtlasNode* node);
		// Resets the entire tree
		void Reset();
		// Updates the node's pixels
		// Params:
		//	node: The node we want to update the pixels to
		//	pixels: The pixels we want to push into the node
		void UpdateNodePixels(AtlasNode* node, const unsigned char* pixels);
		// Updates the whole pixel array
		// Params:
		//	pixels: The pixels to copy over to this tree
		void UpdatePixels(const unsigned char* pixels);
		// Returns: The pixels for the entire texture atlas
		unsigned char* GetPixels() const;
		// Returns: total width of the tree's texture
		unsigned GetWidth() const;
		// Returns: total height of the tree's texture
		unsigned GetHeight() const;
		// Returns: The atlas' id
		unsigned GetID() const;

		// Print this tree!
		// Params:
		//	stream: The stream we are using to output the tree
		//	atlas: The tree we want to print
		// Return: The stream we are using to output the tree
		friend std::ostream& operator<<(std::ostream& stream, const TextureAtlas& atlas);
	};

	// Global Functions
	void PrintNode(std::ostream& stream, const AtlasNode* node, unsigned tabCounter = 0);

}