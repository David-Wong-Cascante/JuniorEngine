/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * Date CreateDd: 26-Apr-18
 * Last Modified: 22-Jan-2019
 * File name: DrawProgram.cpp
 * Description: Write the definition for the shade functionality, especially for the functions that create and destroy said program
*/

// Includes //
#include "DrawProgram.h"	
#include "OpenGLBundle.h"	// OpenGL Stuff

#include <stdlib.h>			// FILE
#include <sstream>			// StringStream
#include <string>			// String functionality
#include <iostream>			// Printing stuff

// Private Member Functions //
int Junior::DrawProgram::CreateShader(int* id, int type, const char** source)
{
	int success = 0;
	char errorInfoLog[256];
	*id = glCreateShader(type);
	glShaderSource(*id, 1, source, NULL);
	glCompileShader(*id);

	glGetShaderiv(*id, GL_COMPILE_STATUS, &success);
	//If we failed to compile, quit out of the program while deleting program again
	if (!success)
	{
		glGetShaderInfoLog(*id, sizeof(errorInfoLog), NULL, errorInfoLog);
		std::string shaderName;
		switch (type)
		{
		case GL_VERTEX_SHADER:
			shaderName = "VERTEX";
			break;
		case GL_FRAGMENT_SHADER:
			shaderName = "FRAGMENT";
			break;
		case GL_GEOMETRY_SHADER:
			shaderName = "GEOMETRY";
			break;
		default:
			shaderName = "UNKNOWN";
			break;
		}
		shaderName += " SHADER";
		std::cout << "Failed to compile the " << shaderName << ":\n" << errorInfoLog << std::endl;
	}

	return success;
}

// Public Member Functions //
Junior::DrawProgram::DrawProgram()
{

}

Junior::DrawProgram::DrawProgram(std::string fileDir)
{
	LoadFromDisk(fileDir);
}


void Junior::DrawProgram::LoadFromDisk(std::string fileDir)
{
	// Get the filepaths for the individual shader files
	std::string vertexShaderLoc = fileDir + ".vs";
	std::string fragmentShaderLoc = fileDir + ".fs";
	// Get the shader text from for Vertex Shader, Fragment Shader, and Geometry Shader
	std::stringstream vertexStream;
	std::stringstream fragmentStream;
	FILE* vertexFile = 0;
	FILE* fragmentFile = 0;
	char textPortion[80];

	// Open the files to get the information from them
	vertexFile = fopen(vertexShaderLoc.c_str(), "rt");
	if (!vertexFile)
	{
		std::cout << "Failed to open the vertex shader: " << vertexShaderLoc << std::endl;
		return;
	}

	// Keep reading the vertex fhile until we have reached the end of the file
	while (!feof(vertexFile))
	{
		fgets(textPortion, 80, vertexFile);
		vertexStream << textPortion;
	}

	// Close the freezer after we have opened it
	// We better not leave it open overnight
	fclose(vertexFile);

	// Open the fragment file and do the same for it
	fragmentFile = fopen(fragmentShaderLoc.c_str(), "rt");
	if (!fragmentFile)
	{
		std::cout << "Failed to open the fragment shader: " << fragmentShaderLoc << std::endl;
		return;
	}

	while (!feof(fragmentFile))
	{
		fgets(textPortion, 80, fragmentFile);
		fragmentStream << textPortion;
	}

	fclose(fragmentFile);

	// Turn the shader sources into normal strings
	std::string vectorString = vertexStream.str();
	std::string fragmentString = fragmentStream.str();
	const char* vertexSource = vectorString.c_str();
	const char* fragmentSource = fragmentString.c_str();

	// Debug stuff
	int success;
	char errorInfoLog[256];

	// Create the shaders and the program to get its ID
	int vertexShaderID = -1, fragmentShaderID = -1;
	if (!CreateShader(&vertexShaderID, GL_VERTEX_SHADER, &vertexSource) || !CreateShader(&fragmentShaderID, GL_FRAGMENT_SHADER, &fragmentSource))
	{
		return;
	}

	// Link the shaders to the program
	programID_ = glCreateProgram();

	glAttachShader(programID_, vertexShaderID);
	glAttachShader(programID_, fragmentShaderID);
	glLinkProgram(programID_);

	// Check for errors in linking the program
	glGetProgramiv(programID_, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID_, sizeof(errorInfoLog), NULL, errorInfoLog);
		std::cout << "Failed to link the program together:\n" << errorInfoLog << std::endl;

		return;
	}

	// We don't need the shaders anymore
	// You've served your purpose
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	// Finally, mark the functions success at creating the program
	// return 1;
}

void Junior::DrawProgram::CleanUp()
{
		// Destroy all the components in the program
		glDeleteProgram(programID_);
		programID_ = -1;
}

void Junior::DrawProgram::Bind() const
{
	if (programID_ != -1)
	{
		glUseProgram(programID_);
	}
}

void Junior::DrawProgram::UnBind()
{
	glUseProgram(0);
}