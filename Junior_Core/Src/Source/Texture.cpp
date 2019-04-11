/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File Name: Texture.cpp
 * Description: Code that helps the game engine with textures
 * Created: 18-Aug-2018
 * Last Modified: 13-Feb-2019
*/

// Includes
#include "Texture.h"

#include <iostream>				// IO stream

#include "OpenGLBundle.h"		// OpenGL functions
#include "Graphics.h"			// Graphics
// STB Image, thank you for saving my butt
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Public Member Functions

Junior::Texture::Texture(unsigned int textureType, bool generateMipMaps, unsigned int textureFormat, unsigned int internalFormat, int textureWidth, int textureHeight, int textureDepth)
{
	// Make sure that the texture's depth is never zero if the rest of the texture's components are indeed set
	if ((textureWidth || textureHeight) && !textureDepth)
	{
		textureDepth = 1;
	}

	dimensions_[0] = textureWidth;
	dimensions_[1] = textureHeight;
	dimensions_[2] = textureDepth;
	formatOfTexture_ = textureFormat;
	internalFormatOfTexture_ = internalFormat;
	typeOfTexture_ = textureType;

	// Create the texture within OpenGL and save its ID in the texture struct
	glGenTextures(1, &textureID_);
	glBindTexture(typeOfTexture_, textureID_);

	switch (typeOfTexture_)
	{
	case GL_TEXTURE_1D:
		glTexImage1D(GL_TEXTURE_1D, 0, internalFormat, textureWidth, 0, textureFormat, GL_UNSIGNED_BYTE, 0);
		break;
	case GL_TEXTURE_2D:
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, textureWidth, textureHeight, 0, textureFormat, GL_UNSIGNED_BYTE, 0);
		break;
	case GL_TEXTURE_3D:
		glTexImage3D(GL_TEXTURE_3D, 0, internalFormat, textureWidth, textureHeight, textureDepth, 0, textureFormat, GL_UNSIGNED_BYTE, 0);
		break;
	case GL_TEXTURE_2D_ARRAY:
		glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, internalFormat, textureWidth, textureHeight, textureDepth);
		CHECK_GL_ERROR();
		break;
	}

	//glTextureParameteri(typeOfTexture_, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTextureParameteri(typeOfTexture_, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTextureParameteri(typeOfTexture_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTextureParameteri(typeOfTexture_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(typeOfTexture_, 0);
}

Junior::Texture::Texture()
{
}

Junior::Texture::~Texture()
{
	CleanUp();
}

void Junior::Texture::CleanUp()
{
	if(pixels_)
		delete[] pixels_;

	pixels_ = nullptr;
	glDeleteTextures(1, &textureID_);
	textureID_ = 0;
}

void Junior::Texture::LoadFromDisk(std::string resourceDir)
{
	int textureWidth, textureHeight, textureChannels;
	unsigned char* pixels = GetPixelsFromFile(resourceDir, &textureWidth, &textureHeight, &textureChannels);

	if (pixels)
	{
		// Copy over the pixels
		pixels_ = new unsigned char[textureWidth * textureHeight * textureChannels];
		memcpy(pixels_, pixels, textureWidth * textureHeight * textureChannels);
		// Flip the texture to turn right side up
		glGenTextures(1, &textureID_);
		glBindTexture(GL_TEXTURE_2D, textureID_);

		// Decide the texture's file format and set the mip maps
		GLenum textureType = textureChannels == 4 ? GL_RGBA : GL_RGB;
		GLenum internalTextureFormat = textureChannels == 4 ? GL_RGBA8 : GL_RGB8;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, textureWidth, textureHeight, 0, textureType, GL_UNSIGNED_BYTE, pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Fill in the Texture struct with data
		typeOfTexture_ = GL_TEXTURE_2D;
		dimensions_[0] = textureWidth;
		dimensions_[1] = textureHeight;
		dimensions_[2] = 0;
		formatOfTexture_ = textureType;
		internalFormatOfTexture_ = GL_RGB8;
	}
	else
	{
		std::cout << "[ERROR]: Failed to load the image: " << resourceDir << std::endl;
	}

	// Clean up the pixels
	stbi_image_free(pixels);
}

const unsigned char* Junior::Texture::GetPixels()
{
	//glReadPixels(0, 0, dimensions_[0], dimensions_[1], formatOfTexture_, typeOfTexture_, pixels_);
	return pixels_;
}

const unsigned& Junior::Texture::GetOpenGLTextureID() const
{
	return textureID_;
}

unsigned Junior::Texture::GetDimension(unsigned index) const
{
	return dimensions_[index];
}

void Junior::Texture::BindTexture() const
{
	glBindTexture(typeOfTexture_, textureID_);
}

void Junior::Texture::AppendedLoadToTextureArray2D(std::string resourceDir)
{
	// If the texture is a 2D or 1D texture then ignore the function call as it only works for 3D texture arrays
	if (typeOfTexture_ != GL_TEXTURE_2D_ARRAY)
	{
		std::cout << "[ERROR]: Attempted to append texture " << resourceDir << "into a texture that is not a 2D array" << std::endl;
		return;
	}
	// Then check whether the texture count is not greater or equal to the texture depth
	if (arrayCount_ >= dimensions_[2])
	{
		std::cout << "[ERROR]: Attempted to add more textures than the capacity could handle" << std::endl;
		return;
	}

	int width = 0;
	int height = 0;
	int channels = 0;
	unsigned char* pixels = nullptr;
	// Attempt to load the texture first
	pixels = Texture::GetPixelsFromFile(resourceDir, &width, &height, &channels);
	// Append the texture
	// If it is the first texture, then set all of its data expect depth
	// -> Bind the texture first
	BindTexture();
	// Set the texture to the correct place, and then increment the number of textures we are holding right now
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, arrayCount_, width, height, 1, formatOfTexture_, GL_UNSIGNED_BYTE, pixels);
	++arrayCount_;
	CHECK_GL_ERROR();
	UnbindTexture();
	// Free the pixels
	if (!arrayCount_)
	{
		dimensions_[0] = width;
		dimensions_[1] = height;
		pixels_ = new unsigned char[width * height * channels];
		memcpy(pixels_, pixels, width * height * channels);
	}

	stbi_image_free(pixels);
}

void Junior::Texture::AppendToArray2D(int width, int height, unsigned char* pixels)
{
	// If the texture is a 2D or 1D texture then ignore the function call as it only works for 3D texture arrays
	if (typeOfTexture_ != GL_TEXTURE_2D_ARRAY)
	{
		std::cout << "[ERROR]: Attempted to append texture " << resourceDir << "into a texture that is not a 2D array" << std::endl;
		return;
	}
	// Then check whether the texture count is not greater or equal to the texture depth
	if (arrayCount_ >= dimensions_[2])
	{
		std::cout << "[ERROR]: Attempted to add more textures than the capacity could handle" << std::endl;
		return;
	}
	// Append the texture
	// If it is the first texture, then set all of its data expect depth
	if (!arrayCount_)
	{
		dimensions_[0] = width;
		dimensions_[1] = height;
		unsigned channels = formatOfTexture_ == GL_RGBA8 ? 4 : 3;
		pixels_ = new unsigned char[width * height * channels];
		memcpy(pixels_, pixels, width * height * channels);
	}
	// -> Bind the texture first
	BindTexture();
	// Set the texture to the correct place, and then increment the number of textures we are holding right now
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, arrayCount_, width, height, 1, formatOfTexture_, GL_UNSIGNED_BYTE, pixels);
	++arrayCount_;
	CHECK_GL_ERROR();
	UnbindTexture();
}

void Junior::Texture::ModifyTextureArray(int index, const unsigned char* pixels)
{
	BindTexture();
	// Set the texture to the correct place, and then increment the number of textures we are holding right now
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, index, dimensions_[0], dimensions_[1], 1, formatOfTexture_, GL_UNSIGNED_BYTE, pixels);
	CHECK_GL_ERROR();
	UnbindTexture();
}

void Junior::Texture::UnbindTexture() const
{
	glBindTexture(typeOfTexture_, 0);
}

// Static Helper Functions
unsigned char* Junior::Texture::GetPixelsFromFile(std::string resourceDir, int* width, int* height, int* channels)
{
	int textureWidth, textureHeight, textureChannels;
	unsigned char* pixels = stbi_load(resourceDir.c_str(), &textureWidth, &textureHeight, &textureChannels, 4);
	if (pixels)
	{
		stbi__vertical_flip(pixels, textureWidth, textureHeight, textureChannels);
	}
	else
	{
		std::cout << "[ERROR]: Failed to load the image: " << resourceDir << std::endl;
		// Clean up the pixels
		stbi_image_free(pixels);
		pixels = nullptr;
	}

	// Set the extra parameters if they exist
	if(width)
		*width = textureWidth;

	if (height)
		*height = textureHeight;

	if (channels)
		*channels = textureChannels;

	return pixels;
}