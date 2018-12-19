/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File Name: Texture.cpp
 * Description: Code that helps the game engine with textures
 * Created: 18-Aug-2018
 * Last Modified: 7-Nov-2018
*/

// Includes //
#include "Texture.h"

#include <iostream>				// IO stream

#include "OpenGLBundle.h"		// OpenGL functions
// STB Image, thank you for saving my butt
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Public Member Functions  //

Junior::Texture::Texture(unsigned int textureFormat, unsigned int textureType, bool generateMipMaps, int textureWidth, int textureHeight, int textureDepth = 0)
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
	typeOfTexture_ = textureType;

	// Create the texture within OpenGL and save its ID in the texture struct
	glGenTextures(1, &textureID_);
	glBindTexture(typeOfTexture_, textureID_);
	//glTextureParameteri(tempTexture->typeOfTexture_, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTextureParameteri(tempTexture->typeOfTexture_, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTextureParameteri(tempTexture->typeOfTexture_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTextureParameteri(tempTexture->typeOfTexture_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	switch (typeOfTexture_)
	{
	case GL_TEXTURE_1D:
		glTexImage1D(GL_TEXTURE_1D, 0, textureFormat, textureWidth, 0, textureFormat, GL_UNSIGNED_BYTE, 0);
		break;
	case GL_TEXTURE_2D:
		glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, textureWidth, textureHeight, 0, textureFormat, GL_UNSIGNED_BYTE, 0);
		break;
	case GL_TEXTURE_3D:
		glTexImage3D(GL_TEXTURE_3D, 0, textureFormat, textureWidth, textureHeight, textureDepth, 0, textureFormat, GL_UNSIGNED_BYTE, 0);
		break;
	}

	glBindTexture(typeOfTexture_, 0);
}

Junior::Texture::Texture()
{
}

void Junior::Texture::CleanUp()
{
	glDeleteTextures(1, &textureID_);
	textureID_ = 0;
}

void Junior::Texture::LoadFromDisk(std::string resourceDir)
{
	int textureWidth, textureHeight, textureChannels;
	pixels_ = stbi_load(resourceDir.c_str(), &textureWidth, &textureHeight, &textureChannels, 0);
	if (pixels_)
	{
		stbi__vertical_flip(pixels_, textureWidth, textureHeight, textureChannels);
		// Flip the texture to turn right side up
		glGenTextures(1, &textureID_);
		glBindTexture(GL_TEXTURE_2D, textureID_);
		// Set the filtering parameters
		//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Decide the texture's file format and set the mip maps
		GLenum inTextureType = textureChannels == 4 ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, inTextureType, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels_);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Fill in the Texture struct with data
		typeOfTexture_ = GL_TEXTURE_2D;
		dimensions_[0] = textureWidth;
		dimensions_[1] = textureHeight;
		dimensions_[2] = 0;
		formatOfTexture_ = inTextureType;
	}
	else
	{
		std::cout << "[ERROR]: Failed to load the default image\n";
		// Clean up the pixels
		stbi_image_free(pixels_);
	}

	// Clean up the pixels
	stbi_image_free(pixels_);
}

const unsigned char* Junior::Texture::GetPixels()
{
	glReadPixels(0, 0, dimensions_[0], dimensions_[1], formatOfTexture_, typeOfTexture_, reinterpret_cast<void*>(pixels_));
	return pixels_;
}

const unsigned& Junior::Texture::GetOpenGLTextureID() const
{
	return textureID_;
}

void Junior::Texture::BindTexture() const
{
	glBindTexture(typeOfTexture_, textureID_);
}

void Junior::Texture::UnbindTexture() const
{
	glBindTexture(typeOfTexture_, 0);
}