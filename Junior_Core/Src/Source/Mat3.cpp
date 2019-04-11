/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Mat3.cpp
* Description: Implement all of the matrix math
* Created: 26-Apr-2018
* Last Modified: 29-Oct-2018
*/

// Includes //
#include "Mat3.h"
#include <string>			// Strings
#include "Vec3.h"			// Vec3

// Helper Function for Matrix Multiplication
float DotProductColumnRow(const Junior::Mat3& lhs, const Junior::Mat3& rhs, int row, int column)
{
	return rhs.m_[4 * row + 0] * lhs.m_[4 * 0 + column] + rhs.m_[4 * row + 1] * lhs.m_[4 * 1 + column]
		+ rhs.m_[4 * row + 2] * lhs.m_[4 * 2 + column] + rhs.m_[4 * row + 3] * lhs.m_[4 * 3 + column];
}

// Global Operators for Mat3 //
Junior::Mat3 Junior::operator+(const Mat3& lhs, const Mat3& rhs)
{
	Mat3 out;

	out.m00_ = lhs.m00_ + rhs.m00_;
	out.m10_ = lhs.m10_ + rhs.m10_;
	out.m20_ = lhs.m20_ + rhs.m20_;
	out.m30_ = lhs.m30_ + rhs.m30_;

	out.m01_ = lhs.m01_ + rhs.m01_;
	out.m11_ = lhs.m11_ + rhs.m11_;
	out.m21_ = lhs.m21_ + rhs.m21_;
	out.m31_ = lhs.m31_ + rhs.m31_;

	out.m02_ = lhs.m02_ + rhs.m02_;
	out.m12_ = lhs.m12_ + rhs.m12_;
	out.m22_ = lhs.m22_ + rhs.m22_;
	out.m32_ = lhs.m32_ + rhs.m32_;

	out.m03_ = lhs.m03_ + rhs.m03_;
	out.m13_ = lhs.m13_ + rhs.m13_;
	out.m23_ = lhs.m23_ + rhs.m23_;
	out.m33_ = lhs.m33_ + rhs.m33_;

	return out;
}

Junior::Mat3 Junior::operator-(const Mat3& lhs, const Mat3& rhs)
{
	Mat3 out;

	out.m00_ = lhs.m00_ - rhs.m00_;
	out.m10_ = lhs.m10_ - rhs.m10_;
	out.m20_ = lhs.m20_ - rhs.m20_;
	out.m30_ = lhs.m30_ - rhs.m30_;
						
	out.m01_ = lhs.m01_ - rhs.m01_;
	out.m11_ = lhs.m11_ - rhs.m11_;
	out.m21_ = lhs.m21_ - rhs.m21_;
	out.m31_ = lhs.m31_ - rhs.m31_;
						
	out.m02_ = lhs.m02_ - rhs.m02_;
	out.m12_ = lhs.m12_ - rhs.m12_;
	out.m22_ = lhs.m22_ - rhs.m22_;
	out.m32_ = lhs.m32_ - rhs.m32_;
						
	out.m03_ = lhs.m03_ - rhs.m03_;
	out.m13_ = lhs.m13_ - rhs.m13_;
	out.m23_ = lhs.m23_ - rhs.m23_;
	out.m33_ = lhs.m33_ - rhs.m33_;

	return out;
}

Junior::Vec3 Junior::operator*(const Mat3& lhs, const Vec3& rhs)
{
	Vec3 out;

	out.x_ = (lhs.m00_ * rhs.x_) + (lhs.m01_ * rhs.y_) + (lhs.m02_ * rhs.z_) + (lhs.m03_ * rhs.w_);
	out.y_ = (lhs.m10_ * rhs.x_) + (lhs.m11_ * rhs.y_) + (lhs.m12_ * rhs.z_) + (lhs.m13_ * rhs.w_);
	out.z_ = (lhs.m20_ * rhs.x_) + (lhs.m21_ * rhs.y_) + (lhs.m22_ * rhs.z_) + (lhs.m23_ * rhs.w_);
	out.w_ = (lhs.m30_ * rhs.x_) + (lhs.m31_ * rhs.y_) + (lhs.m32_ * rhs.z_) + (lhs.m33_ * rhs.w_);
	
	return out;
}

Junior::Mat3 Junior::operator*(const Mat3& lhs, const Mat3& rhs)
{
	Mat3 out;

	for (unsigned i = 0; i < 4; ++i)
	{
		for (unsigned j = 0; j < 4; ++j)
		{
			out.m_[i * 4 + j] = DotProductColumnRow(lhs, rhs, i, j);
		}
	}

	return out;
}

Junior::Mat3& Junior::operator+=(Mat3& lhs, const Mat3& rhs)
{
	lhs.m00_ += rhs.m00_;
	lhs.m10_ += rhs.m10_;
	lhs.m20_ += rhs.m20_;
	lhs.m03_ += rhs.m30_;
	
	lhs.m10_ += rhs.m01_;
	lhs.m11_ += rhs.m11_;
	lhs.m12_ += rhs.m21_;
	lhs.m13_ += rhs.m31_;
	
	lhs.m20_ += rhs.m02_;
	lhs.m21_ += rhs.m12_;
	lhs.m22_ += rhs.m22_;
	lhs.m23_ += rhs.m32_;
	
	lhs.m30_ += rhs.m03_;
	lhs.m31_ += rhs.m13_;
	lhs.m32_ += rhs.m23_;
	lhs.m33_ += rhs.m33_;
	return lhs;
}

Junior::Mat3& Junior::operator-=(Mat3& lhs, const Mat3& rhs)
{
	lhs.m00_ -= rhs.m00_;
	lhs.m10_ -= rhs.m10_;
	lhs.m20_ -= rhs.m20_;
	lhs.m03_ -= rhs.m30_;
			 
	lhs.m10_ -= rhs.m01_;
	lhs.m11_ -= rhs.m11_;
	lhs.m12_ -= rhs.m21_;
	lhs.m13_ -= rhs.m31_;
			 
	lhs.m20_ -= rhs.m02_;
	lhs.m21_ -= rhs.m12_;
	lhs.m22_ -= rhs.m22_;
	lhs.m23_ -= rhs.m32_;
			 
	lhs.m30_ -= rhs.m03_;
	lhs.m31_ -= rhs.m13_;
	lhs.m32_ -= rhs.m23_;
	lhs.m33_ -= rhs.m33_;

	return lhs;
}

Junior::Mat3& Junior::operator*=(Mat3& lhs, const Mat3& rhs)
{
	lhs = lhs * rhs;
	return lhs;
}

Junior::Mat3 Junior::operator*(float scalar, const Mat3& rhs)
{
	Mat3 copy;
	
	copy.m00_ = rhs.m00_ * scalar;
	copy.m01_ = rhs.m01_ * scalar;
	copy.m02_ = rhs.m02_ * scalar;
	copy.m03_ = rhs.m03_ * scalar;

	copy.m10_ = rhs.m10_ * scalar;
	copy.m11_ = rhs.m11_ * scalar;
	copy.m12_ = rhs.m12_ * scalar;
	copy.m13_ = rhs.m13_ * scalar;

	copy.m20_ = rhs.m20_ * scalar;
	copy.m21_ = rhs.m21_ * scalar;
	copy.m22_ = rhs.m22_ * scalar;
	copy.m23_ = rhs.m23_ * scalar;

	copy.m30_ = rhs.m30_ * scalar;
	copy.m31_ = rhs.m31_ * scalar;
	copy.m32_ = rhs.m32_ * scalar;
	copy.m33_ = rhs.m33_ * scalar;
	
	return copy;
}

std::ostream& Junior::operator<<(std::ostream& stream, const Mat3& matrix)
{
	// Print the beginning of the matrix
	stream << "[ ";
	for (unsigned i = 0; i < 4; ++i)
	{
		// Print the column
		stream << *reinterpret_cast<const Vec3*>(4 * i + matrix.m_);
		if (i != 3)
			stream << " , ";
	}
	// Print the end of the matrix
	stream << " ]";

	return stream;
}

std::fstream& Junior::operator<<(std::fstream& stream, const Mat3& matrix)
{
	// Print the beginning of the matrix
	stream << "[ ";
	for (unsigned i = 0; i < 4; ++i)
	{
		// Print the column
		stream << *reinterpret_cast<const Vec3*>(4 *i + matrix.m_);
		if (i != 3)
			stream << " , ";
	}
	// Print the end of the matrix
	stream << " ]";

	return stream;
}

void Junior::operator>>(std::fstream& stream, Mat3& matrix)
{
	std::string skipHelper;
	// Skip the beginning scope
	stream >> skipHelper;
	// Start reading the matrix
	for (unsigned i = 0; i < 4; ++i)
	{
		// Skip the beginning of the vector
		stream >> skipHelper;
		for (unsigned j = 0; j < 4; ++j)
		{
			// Start reading the values inside the vector
			stream >> matrix.m_[i * 4 + j];
			if (j != 3)
				stream >> skipHelper;
		}
		// Skip the end of the vector and start the next one
		if (i != 3)
		{
			// Skip the closing bracket if it we still have columns to go
			stream >> skipHelper;
		}
		stream >> skipHelper;
	}

	// Skip one more time
	stream >> skipHelper;
}