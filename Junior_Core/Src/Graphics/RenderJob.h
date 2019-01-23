#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: RenderJob.h
* Description: Describe the data Graphics is going to use to render stuff to thes screen
* Created: 28-Apr-2018
* Last Modified: 22-Jan-2019
*/

// Includes //
#include "Component.h"

namespace Junior
{
	// Forward Declarations //
	union Vec3;
	union Mat3;

	struct RenderJob
	{
		// Public Struct Variables //
		Mat3* transformation_;
		float textureID_ = 0;
		float atlasUVs_[8] = { 0, 0, 0, 0, 0, 0, 0, 0, };
		ComponentType renderedJobType_;
	};
}