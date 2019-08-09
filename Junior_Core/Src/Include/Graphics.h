#pragma once
/* 
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: Graphics.h
 * Description: Declare the functionality of the window and the renderer under the same class
 * Created: 20 Apr 2018
 * Last Modified: 8 Aug 2019
*/

// Includes //
#include <vector>			// Vector
#include <typeinfo>			// Type Info

#include "RenderJob.h"		// Render Job
#include "OpenGLBundle.h"	// OpenGL Bundle
#include "Mat3.h"			// Mat3
#include "GameSystem.h"		// Game System
#include "DrawProgram.h"	// The Drawing Programs
#include "ResourceManager.h"// Resource Manager

#include "Event.h"			// Event

// Forward Declarations
struct GLFWwindow;

namespace Junior
{

	// Foward Declarations
	class Camera;
	class Texture;
	class TextureAtlas;
	class Input;

	// Event Structs

	struct WindowResizeEvent : public Event
	{
		// Public Member Variables

		// The old width of the window
		int oldWidth_;
		// The new
		int newWidth_;
		// The old height of the window
		int oldHeight_;
		// The new height of the window
		int newHeight_;

		// Public Member Functions

		// Constructor
		WindowResizeEvent()
			: Event(WindowResizeEventName)
		{
		}

		// Public Static Variables

		// The name of the window event
		static std::string WindowResizeEventName;
	};

	struct WindowQuitEvent : public Event
	{
		// Public Member Functions

		WindowQuitEvent()
			: Event(WindowQuitEventName)
		{
		}

		// Public Static Variables

		// The name of the window quit event
		static std::string WindowQuitEventName;
	};


	// Classes

	class Graphics : public GameSystem
	{
	public:
		// Public Member Variables

		// The main camera
		Camera* mainCamera_;
	private:
		// Private Class Variables

		int windowWidth_, windowHeight_;
		int openGLVersionMajor_, openGLVersionMinor_;
		
		// Texture array
		Texture* textureBank_;
		// Let the jank ensue (texture atlas)
		TextureAtlas* atlas_;
		// The window handle
		GLFWwindow* windowHandle_;
		// All of the shaders
		std::vector<DrawProgram*> programs_;
		// Orthographic Matrix
		Mat3 orthographicMatrix_;
		
		// Private Member Functions
		// Hidden Constructors and Assigment Operators
		Graphics();
		Graphics(const Graphics& graphics) = delete;
		Graphics& operator=(const Graphics& other) = delete;
	public:
		// Public Member Functions
		// Loads any assets
		// Returns: Whether it was successful on loading said assets
		bool Load() override;
		// Initializes the window's functions
		// Returns: If the functions successfully initialized the graphics class
		bool Initialize() override;
		// Requests the GLFW api to close the window
		bool WindowRequestClosed();
		// Render the graphics to the window
		void Render() override;
		// Updates the system
		// Params:
		//	dt: The time in between frames
		void Update(double dt) override;
		// Shutdown the graphics
		void Shutdown() override;
		// Unloads any graphics
		void Unload() override;
		// Updates the texture for the texture atlas
		void UpdateTextureAtlas();
		// Sets the dimensions of the window
		// Params:
		//	width: the width of the screen
		//	height: the height of the screen
		void SetDimensions(int width, int height);
		// Poll the window so it actually responds
		void PollWindow();
		// Gets a specfic mesh from the mesh pool
		// Params:
		//	resourceDir: The shader's directory
		template <class T>
		T* GetMesh(const std::string& resourceDir)
		{
			// First attempt to find the program with the same name
			DrawProgram* program = nullptr;
			for (auto citer = programs_.cbegin(); citer != programs_.cend(); ++citer)
			{
				if ((*citer)->GetResourceDir() == resourceDir)
				{
					// We found a shader with the same directory, save it for later
					program = *citer;
					break;
				}
			}

			// If we didn't find the program, then get it from the ResourceManager
			if (!program)
			{
				program = ResourceManager::GetInstance().GetResource<DrawProgram>(resourceDir);
				// and add it to the programs
				programs_.push_back(program);
			}

			// Then try getting the mesh from the program
			return program->GetMesh<T>();
		}
		// Returns: The window's with
		int GetWindowWidth() const;
		// Returns: The window's height
		int GetWindowHeight() const;
		// Returns: The texture atlas
		TextureAtlas* GetTextureAtlas();
		// Returns: The singleton instance of this class
		static Graphics& GetInstance();
	};

	// The function callback that changes the viewport
	// Params:
	//	window: The window that is being resized
	//	width: The new width of the window
	//	height: The new height of the window
	void WindowResizeCallback(GLFWwindow* window, int width, int height);
	// The function callback that quits the application
	void WindowQuitCallback(GLFWwindow* window);
	// OpenGL error identifying function
	// Params:
	//	id: The error id
	// Returns: The name of the error
	const char* IdentifyGLError(unsigned id);
	// OpenGL error identifying function
	// Params:
	//	severity: The enum for the severity
	//Returns: The name of the severity
	const char* IdentifyGLSeverity(unsigned severity);
	// Callback function when GL fires an error
	// Params:
	//	source: The source of the error
	//	type: The type of error produced
	//	severity: The severity of the error
	//	id: The error's id
	//	length: Length of the error message
	//	message: The error message
	//	userParam: Any user defined object
	// Source: https://www.khronos.org/opengl/wiki/OpenGL_Error
	void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const char* message, const void* userParam);
}