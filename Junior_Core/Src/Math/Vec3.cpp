/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* Created: 24-Apr-2018
* Last Modified: 29-Oct-2018
* Description: Declare the functionality of the Vector2 used on this game engine
* File Name: Vec3.cpp
*/

#include "Vec3.h"
// For printing the vectors
#include <iostream>				// IO Stream

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

void Junior::operator+=(Vec3& lhs, const Vec3& rhs)
{
	lhs.x_ += rhs.x_;
	lhs.y_ += rhs.y_;
	lhs.z_ += rhs.z_;
}

void Junior::operator-=(Vec3& lhs, const Vec3& rhs)
{
	lhs.x_ -= rhs.x_;
	lhs.y_ -= rhs.y_;
	lhs.z_ -= rhs.z_;
}

void Junior::operator*=(Vec3& lhs, float scalar)
{
	lhs.x_ *= scalar;
	lhs.y_ *= scalar;
	lhs.z_ *= scalar;
}

void Junior::operator/=(Vec3& lhs, float scalar)
{
	lhs.x_ /= scalar;
	lhs.y_ /= scalar;
	lhs.z_ /= scalar;
}

// Global Functions //

void Junior::PrintVector(const Vec3& vec)
{
	printf("[%f, %f, %f, %f]\n", vec.x_, vec.y_, vec.z_, vec.w_);
}