/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* Created: 24-Apr-2018
* Last Modified: 6-May-2018
* Description: Write the extra functionality for the linear algebra used in the engine
* File Name: LinearMath.cpp
*/

// Includes //
#include "LinearMath.h"

#include <math.h>			// Math

#include "Mat3.h"			// Mat3
#include "Vec3.h"			// Vec3

// Global Functions //

float Junior::DotProduct(const Vec3& lhs, const Vec3& rhs)
{
	return lhs.x_ * rhs.x_ + lhs.y_ * rhs.y_ + lhs.z_ * rhs.z_;
}

float Junior::LengthSq(const Vec3& vec)
{
	return vec.x_ * vec.x_ + vec.y_ * vec.y_ + vec.z_ * vec.z_;
}

float Junior::Length(const Vec3& vec)
{
	return sqrtf(LengthSq(vec));
}

Junior::Vec3 Junior::Project(const Vec3& from, const Vec3& to)
{
	return to * (DotProduct(to, from) / DotProduct(to, to));
}

Junior::Vec3 Junior::Normalized(const Vec3& vec)
{
	float vecLength = Length(vec);
	Vec3 out;
	out.x_ = vec.x_ / vecLength;
	out.y_ = vec.y_ / vecLength;
	out.z_ = vec.z_ / vecLength;
	return out;
}

Junior::Vec3 Junior::CrossProduct(const Vec3& lhs, const Vec3& rhs)
{
	// Temp return value
	return { 0, 1, 0, 0 };
}

// TRUST ME, THE MATRICES LOOK LIKE THEIR IN ROW-MAJOR ORDER, BUT THEY'RE IN COLUMN MAJOR ORDER

Junior::Mat3 Junior::Orthographic(float left, float right, float top, float bottom, float zNear, float zFar)
{
	return
	{
		2.0f / (right - left),								0.0f,						0.0f,					-(right+left)/(right-left),
		0.0f,								2.0f / (top - bottom),						0.0f,					-(top+bottom)/(top-bottom),
		0.0f,												0.0f,						-2.0f / (zFar - zNear),	-(zFar+zNear)/(zFar-zNear),
		0.0f,												0.0f,						0.0f,					1,
	};
}

Junior::Mat3 Junior::Perspective(float fov, float width, float height, float zNear, float zFar)
{
	float aspectRatio = width / height;
	float zRange = zFar - zNear;
	float angleInRadians = fov * (static_cast<float>(PI) / 180.0f);
	float tanHalfFOV = tanf(angleInRadians / 2.0f);

	return
	{
		1.0f / tanHalfFOV,					0.0f,						0.0f,						0.0f,
		0.0f,					1.0f / tanHalfFOV,						0.0f,						0.0f,
		0.0f,								0.0f,				-zFar / zRange,		-(zFar * zNear) / zRange,
		0.0f,								0.0f,						-1.0f,						0.0f,
	};
}

Junior::Mat3 Junior::Translation(const Junior::Vec3& vec)
{
	return 
	{
		1.0,	0.0,	0.0,	0.0f,
		0.0,	1.0,	0.0,	0.0f,
		0.0,	0.0f,	1.0f,	0.0f,
		vec.x_,	vec.y_,	vec.z_,	1.0f,
	};
}

Junior::Mat3 Junior::Scale(const Junior::Vec3& vec)
{
	return 
	{
		vec.x_,	0.0f,	0.0f,	0.0f,
		0.0f,	vec.y_,	0.0f,	0.0f,
		0.0f,	0.0f,	vec.z_,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f,
	};
}

Junior::Mat3 Junior::Rotation(float angle)
{
	return
	{
		cosf(angle),	sinf(angle),	0.0f,	0.0f,
		-sinf(angle),	cosf(angle),	0.0f,	0.0f,
		0.0f,			0.0f,			1.0f,	0.0f,
		0.0f,			0.0f,			0.0f,	1.0f,
	};
}

Junior::Mat3 Junior::Transpose(const Junior::Mat3& mat)
{
	Mat3 copy;
	for (unsigned i = 0; i < 4; ++i)
	{
		for (unsigned j = 0; j < 4; ++j)
		{
			copy.m_[j * 4 + i] = mat.m_[i * 4 + j];
		}
	}
	return copy;
}

Junior::Mat3 Junior::Identity()
{
	return {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};
}