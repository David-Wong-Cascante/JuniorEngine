#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Mat3.h
* Description: Tell the compiler what a 3x3 matrix can do before actually telling them how (column major order)
* Created: 26-Apr-2018
* Last Modified: 29-Oct-2018
*/

#include <iostream>			// IO stream
#include <fstream>			// File Stream

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

	// Adds two matrices together
	// Params:
	//	lhs: The left matrix
	//	rhs: The right matrix
	// Returns: Returns the added matrix
	Mat3 operator+(const Mat3& lhs, const Mat3& rhs);
	// Rests two matrices together
	// Params:
	//	lhs: The left matrix
	//	rhs: The right matrix
	// Returns: The left subtracted from the right
	Mat3 operator-(const Mat3& lhs, const Mat3& rhs);
	// Multiplies two matrices together
	// Params:
	//	lhs: The left matrix
	//	rhs: The right matrix
	// Returns: The multiplied the two matrices
	Mat3 operator*(const Mat3& lhs, const Mat3& rhs);
	// Multiplies the matrix and a float
	// Params:
	//	lhs: The left scalar
	//	rhs: The right vector
	// Returns: The scaled matrix
	Mat3 operator*(float lhs, const Mat3& rhs);
	// Multiplies a matrix and a vector
	// Params:
	//	lhs: The left matrix
	//	rhs: The right vector
	// Returns: The transformed vector
	Vec3 operator*(const Mat3& lhs, const Vec3& rhs);
	// Adds a matrix into another
	// Params:
	//	lhs: The left matrix
	//	rhs: The right matrix
	// Returns: The left matrix post addition
	Mat3& operator+=(Mat3& lhs, const Mat3& rhs);
	// Subtracts one matrix from another
	// Params:
	//	lhs: The left matrix
	//	rhs: The right matrix
	// Returns: The left matrix post subtraction
	Mat3& operator-=(Mat3& lhs, const Mat3& rhs);
	// Multiplies a matrix by another
	// Params:
	//	lhs: The left matrix
	//	rhs: The right matrix
	// Returns: The left matrix post addition
	Mat3& operator*=(Mat3& lhs, const Mat3& rhs);
	// Prints a matrix into a output stream
	// Params:
	//	stream: The stream we are printing to
	//	matrix: The matrix we are printing
	// Returns: The output stream
	std::ostream& operator<<(std::ostream& stream, const Mat3& matrix);
	// Prints a matrix into a file stream
	// Params:
	//	stream: The file stream we are printing to
	//	matrix: The matrix we are printing
	// Returns: The output file stream
	std::fstream& operator<<(std::fstream& stream, const Mat3& matrix);
	// Reads a matrix from a file stream
	// Params:
	//	stream: The file stream we are reading from
	//	matrix: The matrix we are saving to
	void operator>>(std::fstream& stream, Mat3& matrix);
}
