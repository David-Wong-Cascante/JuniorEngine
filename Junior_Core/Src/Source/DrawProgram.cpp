/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: DrawProgram.cpp
 * Date CreateDd: 26 Apr 2018
 * Last Modified: 6 May 2019
 * Description: Write the definition for the shade functionality, especially for the functions that create and destroy said program
*/

// Includes //
#include "DrawProgram.h"	
#include "OpenGLBundle.h"	// OpenGL Stuff

#include <stdlib.h>			// FILE
#include <sstream>			// StringStream
#include <string>			// String functionality
#include "Debug.h"			// Debug Info
#include "Mesh.h"			// Mesh

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
		Debug& debug = Debug::GetInstance();
		debug.Print(debug.GetDebugLevelName(DebugLevel::ERROR));
		debug.Print("Failed to compile ");
		debug.Print(shaderName);
		debug.PrintLn(":");
		debug.PrintLn(errorInfoLog);
	}

	return success;
}

// Public Member Functions
Junior::DrawProgram::DrawProgram()
{
}

Junior::DrawProgram::DrawProgram(const DrawProgram& other)
	: Resource(other), programID_(other.programID_)
{
}

Junior::DrawProgram::DrawProgram(const std::string& fileDir)
{
	LoadFromDisk(fileDir);
}

Junior::DrawProgram::~DrawProgram()
{
	// Remove all of the meshes and delete them
	for (auto citer = meshes_.begin(); citer != meshes_.cend(); ++citer)
	{
		delete *citer;
	}

	meshes_.clear();
}

void Junior::DrawProgram::LoadFromDisk(const std::string& fileDir)
{
	// Debug logging
	Debug& debug = Debug::GetInstance();
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
		debug.Print(DebugLevel::ERROR);
		debug.Print("Failed to open the vertex shader: ");
		debug.PrintLn(vertexShaderLoc);
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
		debug.Print(DebugLevel::ERROR);
		debug.Print("Failed to open the fragment shader: ");
		debug.PrintLn(fragmentShaderLoc);
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
		debug.Print(DebugLevel::ERROR);
		debug.PrintLn("Failed to link the program together: ");
		debug.PrintLn(errorInfoLog);
		return;
	}

	// We don't need the shaders anymore
	// You've served your purpose
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	// Finally, mark the functions success at creating the program
	// return 1;
}

void Junior::DrawProgram::Draw()
{
	// Draw every mesh
	for (auto iter = meshes_.begin(); iter != meshes_.end(); ++iter)
	{
		(*iter)->StartBinding();
		(*iter)->Draw();
		(*iter)->EndBinding();
	}
}

void Junior::DrawProgram::CleanUp()
{
		// Destroy all the components in the program
		glDeleteProgram(programID_);
		programID_ = -1;
}

void Junior::DrawProgram::AddMesh(Mesh* mesh)
{
	meshes_.push_back(mesh);
}

void Junior::DrawProgram::Bind() const
{
	if (programID_ != -1)
	{
		glUseProgram(programID_);
	}
}

void Junior::DrawProgram::UnBind() const
{
	glUseProgram(0);
}