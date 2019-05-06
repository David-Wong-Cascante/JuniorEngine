/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: DrawProgram.h
* Date Created: 26 Apr 2018
* Last Modified: 6 May 2019
* Description: Declare what a Draw Program is
*/

// Includes //
#include <vector>		// Vector
#include "Resource.h"	// Resource

namespace Junior
{
	// Forward Declarations
	class Mesh;

	class DrawProgram : public Resource
	{
	private:
		// Private Member Variables

		// The meshes we are drawing
		std::vector<Mesh*> meshes_;
		// Private Member Functions

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
		
		// Public Member Functions //
		// Constructors 
		// Creates an empty Draw Program
		DrawProgram();
		// Copy Constructor
		DrawProgram(const DrawProgram& other);
		// Creates a Draw Program from shader files
		DrawProgram(const std::string& fileName);
		// Destructor
		~DrawProgram();
		// Loads a shader file from the disk
		// Params:
		//	fileDir: the directory where the shader files are found
		void LoadFromDisk(const std::string& fileDir) override;
		// Draw all of the meshes in the shader
		void Draw();
		// Cleans up any resources left in this shader
		void CleanUp() override;
		// Adds a mesh to the draw program
		// Params:
		//	mesh: The mesh we are adding to the program
		void AddMesh(Mesh* mesh);
		// Gets a mesh with an equivalent type
		// Returns: The mesh with the same type
		template <typename T>
		T* GetMesh()
		{
			// First attempt to find the mesh
			for (auto citer = meshes_.cbegin(); citer != meshes_.cend(); ++citer)
			{
				if (typeid((*citer)) == typeid(T) || dynamic_cast<T*>(*citer))
				{
					return static_cast<T*>(*citer);
				}
			}

			// Else, create the mesh
			T* mesh = new T;
			AddMesh(mesh);
			return mesh;
		}
		// Binds the program to OpenGL
		void Bind() const;
		// Unbinds all programs from OpenGL
		void UnBind() const;
	};
}