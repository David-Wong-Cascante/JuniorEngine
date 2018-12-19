#pragma once
/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * Created: 24-Apr-2018
 * Last Modified: 29-Oct-2018
 * Description: Declare the functionality of the Vector2 used on this game engine
 * File Name: Vec3.h
*/
namespace Junior
{
	union Vec3
	{
		// Public Union Variables //
		float m_[4] = { 0, 0, 0, 1};
		struct
		{
			float x_, y_, z_, w_;
		};

		// Public Member Functions
		Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);

	};

	// Global Operators for Vec3 //
	Vec3 operator+(const Vec3& lhs, const Vec3& rhs);
	Vec3 operator-(const Vec3& lhs, const Vec3& rhs);
	Vec3 operator*(const Vec3& lhs, float scalar);
	Vec3 operator/(const Vec3& lhs, float scalar);

	Vec3 operator*(float scalar, const Vec3& rhs);

	void operator+=(Vec3& lhs, const Vec3& rhs);
	void operator-=(Vec3& lhs, const Vec3& rhs);
	void operator*=(Vec3& lhs, float scalar);
	void operator/=(Vec3& lhs, float scalar);

	// Global Functions //
	void PrintVector(const Vec3& vec);
}