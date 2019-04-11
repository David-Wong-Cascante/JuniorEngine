#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: RenderJob.h
* Description: Describe the data Graphics is going to use to render stuff to thes screen
* Created: 28-Apr-2018
* Last Modified: 14-Feb-2019
*/

// Includes //
#include "OpenGLBundle.h"
#include "Mat3.h"
#include "Vec3.h"

namespace Junior
{
	struct RenderJob
	{
		// Public Struct Variables //
		Mat3 transformation_;
		// Where x and y are the translation and (z, w) is the scale
		Vec3 uvTranslationAndScale_ = Vec3(0, 0, 1.0f, 1.0f);
		unsigned int textureID_ = 0;
	};
}