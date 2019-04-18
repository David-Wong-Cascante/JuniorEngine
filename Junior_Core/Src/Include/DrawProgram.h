/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* Date CreateDd: 26-Apr-18
* Last Modified: 29-Oct-18
* File name: DrawProgram.h
* Description: Declare what a Draw Program is
*/

// Includes //
#include <map>			// Hash Map
#include "Resource.h"	// Resource

namespace Junior
{
	class DrawProgram : Resource
	{
	private:
		// Private Class Variables //
		// Creates a shader to add it to the program
		// Params:
		//	id: Returns the id of the shader
		//	type: The type of the shader to be compiled
		//	source: The shader's source code
		// Returns:
		//	The status of the shader's compilation
		int CreateShader(int* id, int type, const char** source);
	public:
		// Public Class Variables //
		int programID_ = -1;
		std::map<const char*, int> uniforms_;
		
		// Public Member Functions //
		// Constructors 
		// Creates an empty Draw Program
		DrawProgram();
		// Copy Constructor
		DrawProgram(DrawProgram& other);
		// Creates a Draw Program from shader files
		DrawProgram(std::string fileName);

		// Loads a shader file from the disk
		// Params:
		//	fileDir: the directory where the shader files are found
		void LoadFromDisk(const std::string& fileDir) override;

		// Cleans up any resources left in this shader
		void CleanUp() override;

		// Binds the program to OpenGL
		void Bind() const;

		// Unbinds all programs from OpenGL
		inline static void UnBind();
	};
}