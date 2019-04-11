#pragma once
/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * Created: 24-Apr-2018
 * Last Modified: 29-Oct-2018
 * Description: Declare the functionality of the Vector2 used on this game engine
 * File Name: Vec3.h
*/

// Includes
#include <ostream>
#include <fstream>

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
	// Adds two vectors together
	// Params:
	//	lhs: The left side of the addition
	//	rhs: The right side of the addition
	// Returns: The added vector
	Vec3 operator+(const Vec3& lhs, const Vec3& rhs);
	// Subtracts two vectors together
	// Params:
	//	lhs: The left side of the subtraction
	//	rhs: The right side of the subtraction
	// Returns: The subtracted vector
	Vec3 operator-(const Vec3& lhs, const Vec3& rhs);
	// Scales a vector
	// Params:
	//	lhs: Left hand side vector
	//	scalar: The scalar we are multiplying by
	// Returns: The scaled vector
	Vec3 operator*(const Vec3& lhs, float scalar);
	// Scales a vector by dividing it
	// Params:
	//	lhs: Left hand side vector
	//	scalar: The scalar we are dividing by
	// Returns: The scaled vector
	Vec3 operator/(const Vec3& lhs, float scalar);
	// Scales a vector
	// Params:
	//	scalar: The scalar we are multiplying by
	//	rhs: Right hand side vector
	// Returns: The scaled vector
	Vec3 operator*(float scalar, const Vec3& rhs);
	// Adds one vector onto the other
	// Params:
	//	lhs: The vector we are adding to
	//	rhs: The added vector
	Vec3& operator+=(Vec3& lhs, const Vec3& rhs);
	// Subtracts one vector onto another
	// Params:
	//	lhs: The vector we are subtractiong from
	//	rhs: The vector we are subtracting
	// Returns: The subtracted vector
	Vec3& operator-=(Vec3& lhs, const Vec3& rhs);
	// Scales a vector
	// Params:
	//	lhs: The scaled vector
	//	scalar: The scalar
	Vec3& operator*=(Vec3& lhs, float scalar);
	// Scales a vector
	// Params:
	//	lhs: The scaled vector
	//	scalar: The scalar we are dividng by
	// Returns: The scaled vector
	Vec3& operator/=(Vec3& lhs, float scalar);
	// Prints a vector onto a stream
	// Params:
	//	stream: The output stream we are outputing to
	//	vector: The vector we are printing
	// Returns: The output stream
	std::ostream& operator<<(std::ostream& stream, const Vec3& vector);
	// Prints a vector onto a file
	// Params:
	//	stream: The file stream we are outputing to
	//	vector: The vector we are printing
	// Returns: The output stream
	std::fstream& operator<<(std::fstream& stream, const Vec3& vector);
	// Reads a vector from a file
	// Params:
	//	stream: The file stream we are reading from
	//	vector: The vector we are saving
	void operator>>(std::fstream& stream, Vec3& vector);
}