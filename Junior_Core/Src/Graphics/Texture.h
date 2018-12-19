#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Texture.h
* Description: Describe and write the functionality of the Texture data used by the Junior game Engine
* Created: 5-Aug-2018
* Last Modified: 29-Oct-2018
*/

// Includes //
#include <string>

#include "Resource.h"

namespace Junior
{
	class Texture : public Resource
	{
	private:
		// Private Class Variables //
		// The texture's id inside of OpenGL
		unsigned int textureID_ = 0;
		// Whether the texture is 1D, 2D, or 3D
		unsigned int typeOfTexture_ = 0;
		// Whether the texture is RGB, RGBA, BRG, etc. (as an OpenGL enum)
		unsigned int formatOfTexture_ = 0;
		// Index 0 is the width of the texture, index 1 is the height of the texture, index 2 is for the depth of the image (3D textures)
		unsigned int dimensions_[3] = { 0, 0, 0 };
		// The pixels of the image
		unsigned char* pixels_ = nullptr;
	public:
		// Public Member Functions ///
		// Creates an empty texture with the size specified
		// Params:
		//	textureFormat: The texture's format
		//	textureType: 1D, 2D, or 3D texture
		//	generateMipMaps: Are we generating mipmaps for this texture
		//	textureWidth: width
		//	textureHeight: height
		//	textureDepth: Usually 1 if it is not a 3D texture, otherwise it is how big the texture is on the 3rd dimension
		Texture(unsigned int textureFormat, unsigned int textureType, bool generateMipMaps, int textureWidth, int textureHeight, int textureDepth);

		// Creates a empty texture
		Texture();

		// Loads a texture from disk
		// Params:
		//	resouceDir: The location the resource is located
		void LoadFromDisk(std::string resourceDir) override;
		// Cleans up the texture
		void CleanUp() override;

		// Returns: The ID OpenGL gave to this texture
		const unsigned& GetOpenGLTextureID() const;
		// Bind the texture to the current shader
		void BindTexture() const;
		// Unbinds the texture from the current shader
		void UnbindTexture() const;
		// Returns: the pixels made by OpenGL of the texture
		const unsigned char* GetPixels();
	};
}