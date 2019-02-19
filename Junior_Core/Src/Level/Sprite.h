#pragma once
/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File Name: Sprite.h
 * Description: Sprites manage the raw data that comes from textures and updates the texture coordinates for texture maps
 * Created: 13-Feb-2019
 * Last Modified: 13-Feb-2019
*/

// Includes
#include "Component.h"				// Component
#include <string>					// Strings

namespace Junior
{
	// Forward Declarations
	class MemoryManager;
	class Texture;
	struct AtlasNode;
	struct RenderJob;

	class Sprite : public Component
	{
	private:
		// Private Member Variables

		// The sprite's texture
		Texture* texture_;
		// The node of the texture atlas we are using
		AtlasNode* atlasNode_;
		// The object's render job
		RenderJob* job_;
	public:
		// Public Member Functions

		// Constructs an empty sprite component
		Sprite();
		// Constructs a sprite component with texture data from a file
		// Params:
		//	path: The path to the imag file
		Sprite(const std::string& path);
		// Initializes the component
		void Initialize() override;
		// Updates the component
		// Params:
		//	dt: The time in between frames
		void Update(double dt) override;
		// Cleans up the component
		// Params:
		//	The memory manager used to create this object
		void Clean(MemoryManager* manager) override;
		// Modifies the sprite's UV modification
		// Params:
		//	xOffset: The x offset
		//	yOffset: The y offset
		//	xScale: The xscale
		//	yScale: The y scale
		void SetUVModifications(float xOffset, float yOffset, float xScale, float yScale);
		// Modfies the sprite's UV modification
		// Params:
		//	xOffset: The x offset
		//	yOffset: The y offset
		void SetUVModifications(float xOffset, float yOffset);
		// Loads an image to the sprite's texture
		// Params:
		//	path: The path to the image file
		void LoadFromDisk(const std::string& path);
		// Gets the immediate texture from this sprite
		// Returns: The sprite's texture
		Texture* GetTexture() const;
		// Returns: The atlas node used to store this sprite's subtexture
		AtlasNode* GetNode() const;
	};
}