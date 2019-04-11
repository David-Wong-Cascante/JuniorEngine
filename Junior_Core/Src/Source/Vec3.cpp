/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* Created: 24-Apr-2018
* Last Modified: 29-Oct-2018
* Description: Declare the functionality of the Vector2 used on this game engine
* File Name: Vec3.cpp
*/

#include "Vec3.h"
#include <string>			// Strings

// Public Member Functions //
Junior::Vec3::Vec3(float x, float y, float z, float w)
{
	x_ = x;
	y_ = y;
	z_ = z;
	w_ = w;
}

// Global Operators for Vec 3 //
Junior::Vec3 Junior::operator+(const Vec3& lhs, const Vec3& rhs)
{
	Vec3 out;
	out.x_ = lhs.x_ + rhs.x_;
	out.y_ = lhs.y_ + rhs.y_;
	out.z_ = lhs.z_ + rhs.z_;
	return out;
}

Junior::Vec3 Junior::operator-(const Vec3& lhs, const Vec3& rhs)
{
	Vec3 out;
	out.x_ = lhs.x_ - rhs.x_;
	out.y_ = lhs.y_ - rhs.y_;
	out.z_ = lhs.z_ - rhs.z_;
	return out;
}

Junior::Vec3 Junior::operator*(const Vec3& lhs, float scalar)
{
	Vec3 out;
	out.x_ = lhs.x_ * scalar;
	out.y_ = lhs.y_ * scalar;
	out.z_ = lhs.z_ * scalar;
	return out;
}

Junior::Vec3 Junior::operator*(float scalar, const Vec3& rhs)
{
	return operator*(rhs, scalar);
}

Junior::Vec3 Junior::operator/(const Vec3& lhs, float scalar)
{
	Vec3 out;
	out.x_ = lhs.x_ / scalar;
	out.y_ = lhs.y_ / scalar;
	out.z_ = lhs.y_ / scalar;
	return out;
}

Junior::Vec3& Junior::operator+=(Vec3& lhs, const Vec3& rhs)
{
	lhs.x_ += rhs.x_;
	lhs.y_ += rhs.y_;
	lhs.z_ += rhs.z_;
	return lhs;
}

Junior::Vec3& Junior::operator-=(Vec3& lhs, const Vec3& rhs)
{
	lhs.x_ -= rhs.x_;
	lhs.y_ -= rhs.y_;
	lhs.z_ -= rhs.z_;
	return lhs;
}

Junior::Vec3& Junior::operator*=(Vec3& lhs, float scalar)
{
	lhs.x_ *= scalar;
	lhs.y_ *= scalar;
	lhs.z_ *= scalar;
	return lhs;
}

Junior::Vec3& Junior::operator/=(Vec3& lhs, float scalar)
{
	lhs.x_ /= scalar;
	lhs.y_ /= scalar;
	lhs.z_ /= scalar;
	return lhs;
}

std::ostream& Junior::operator<<(std::ostream& stream, const Junior::Vec3& vector)
{
	stream << "[ " << vector.x_ << ", " << vector.y_ << ", " << vector.z_ << ", " << vector.w_ << " ]";
	return stream;
}

std::fstream& Junior::operator<<(std::fstream& stream, const Junior::Vec3& vector)
{
	stream << "[ " << vector.x_ << ", " << vector.y_ << ", " << vector.z_ << ", " << vector.w_ << " ]";
	return stream;
}

void Junior::operator>>(std::fstream& stream, Junior::Vec3& vector)
{
	std::string skipHelper;
	// Skip the starting bracket
	stream >> skipHelper;
	for (unsigned i = 0; i < 4; ++i)
	{
		// Read a portion of the vector and skip the text afterwards
		stream >> vector.m_[i];
		stream >> skipHelper;
	}
}