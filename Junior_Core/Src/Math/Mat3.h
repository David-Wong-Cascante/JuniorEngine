#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Mat3.h
* Description: Tell the compiler what a 3x3 matrix can do before actually telling them how
* Created: 26-Apr-2018
* Last Modified: 29-Oct-2018
*/

namespace Junior
{
	union Vec3;
	union Mat3
	{
		// Public Union Variables //
		float m_[16];
		struct
		{
			float m00_, m10_, m20_, m30_, m01_, m11_, m21_, m31_, m02_, m12_, m22_, m32_, m03_, m13_, m23_, m33_;
		};
	};

	// Global Operators for Mat3 //
	Mat3 operator+(const Mat3& lhs, const Mat3& rhs);
	Mat3 operator-(const Mat3& lhs, const Mat3& rhs);
	Mat3 operator*(const Mat3& lhs, const Mat3& rhs);
	Mat3 operator*(float lhs, const Mat3& rhs);
	Vec3 operator*(const Mat3& lhs, const Vec3& rhs);

	Mat3& operator+=(Mat3& lhs, const Mat3& rhs);
	Mat3& operator-=(Mat3& lhs, const Mat3& rhs);
	Mat3& operator*=(Mat3& lhs, const Mat3& rhs);

	// Global Functions //
	void PrintMatrix(const Mat3& mat);
}
