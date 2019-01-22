/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * Date Created: 24-Apr-2018
 * Last Modified: 24-Apr-2018
 * Description: Bundle the OpenGL includes into one organized include, so that Visual Studio doesn't get mad at me anymore
*/

#pragma once
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>
// Use the GLFW functionality
#include <GLFW/glfw3.h>

#define CHECK_GL_ERROR()																										\
GLenum err;																														\
while ((err = glGetError()) != GL_NO_ERROR)																						\
	std::cout << "[GL Error in line " << __LINE__ << ", file: " << __FILE__ << "]: " << IdentifyGLError(err) << std::endl;		\
																					