/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* Created: 24-Apr-2018
* Last Modified: 29-Oct-2018
* Description: Declare the extra vector and matrix math
* File Name: LinearMath.h
*/

// Includes //
//#include "Vec3.h"
//#include "Mat3.h"

// DEFINES //
// Define the conversion between Radians and Degrees
#define PI 3.14159
#define DEG_TO_RAD PI / 180.0
#define RAD_TO_DEG 180.0 / PI

namespace Junior
{
	// Forward Declarations
	union Vec3;
	union Mat3;

	// Global Functions //
	// Gives the dot product between two vectors
	// Params:
	//	lhs: One of the vectors
	//	rhs: The other vector
	// Returns: The dot product between both vectors
	float DotProduct(const Vec3& lhs, const Vec3& rhs);
	// Gives the squared length of a vector
	// Params:
	//	vec: The vector we want to figure the squared length for
	// Returns: The squared length of the vector
	float LengthSq(const Vec3& vec);
	// Gives the magnitude of the vector
	// Params:
	//	vec: The vector we want to figure out the lenght for
	// Returns: The length of the vector
	float Length(const Vec3& vec);
	// Gives a normalized version of the vector
	// Params:
	//	vec3: The vector we want to normalize
	// Returns: The normalized version of the vector
	Vec3 Normalized(const Vec3& vec);
	// Gives the cross product between two vectors
	// Params:
	//	lhs: One of the vectors we want to compare for the cross product
	//	rhs: The other of the vectors we want to compare for the cross product
	// Returns: A cross product between both vectors
	Vec3 CrossProduct(const Vec3& lhs, const Vec3& rhs);
	// Projects a point onto a vector
	// Params:
	//	from: The point we want to project
	//	to: The vector we are projecting into
	// Returns: The projected point
	Vec3 Project(const Vec3& from, const Vec3& to);

	// Creates an orthographic projection matrix
	// Params:
	//	left: Distance in pixels towards the left of the screen from the middle
	//	right: Distance in pixels towards the right of the screen from the middle
	//	top: Distance in pixels towards the top of the screen from the middle
	//	bottom: Distance in pixels towards the bottom of the screen from the middle
	//	zNear: The distance to the nearest Z clipping plane
	//	zFar: The farthest Z clipping plane
	// Returns: The orthographic projection matrix based on the parameters
	Mat3 Orthographic(float left, float right, float top, float bottom, float zNear, float zFar);
	// Creates a perspective projection matrix
	// Params:
	//	fov: The field of view
	//	width: The width of the screen in pixels
	//	height: The height of the scree in pixels
	//	zNear: The distance to the nearest Z clipping plane
	//	zFar: The distance to the farthest Z clipping plane
	// Returns: The perspective projection matrix
	Mat3 Perspective(float fov, float width, float height, float zNear, float zFar);
	// Creates a translation matrix
	// Params:
	//	translation: The vector we want to translate by
	// Returns: The translation matrix with the translation provided
	Mat3 Translation(const Vec3& translation);
	// Creates a scale matrix
	// Params:
	//	scaling: The vector we want to scale by
	// Returns: The scale matrix with the scale factors provided
	Mat3 Scale(const Vec3& scaling);
	// Creates a rotation matrix around the Z axis
	// Params:
	//	angle: The angle we want to rotate by
	// Returns: The rotation matrix around the Z axis by the provided angle
	Mat3 Rotation(float angle);
	
	// Transposes the matrix
	// Params:
	//	mat: The matrix we want to transpose
	// Returns: The transposed matrix for a Mat3
	Mat3 Transpose(const Mat3& mat);
	// Returns: The idendity matrix for a Mat3
	Mat3 Identity();
}