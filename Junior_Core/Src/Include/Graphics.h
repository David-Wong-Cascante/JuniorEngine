#pragma once
/* 
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: Graphics.h
 * Description: Declare the functionality of the window and the renderer under the same class
 * Created: 20-Apr-2018
 * Last Modified: 18-Feb-2019
*/

// Includes //
#include "RenderJob.h"		// Render Job
#include <vector>			// Vector
#include "OpenGLBundle.h"	// OpenGL Bundle
#include "Mat3.h"			// Mat3
#include "GameSystem.h"		// Game System

// Forward Declarations
struct GLFWwindow;

namespace Junior
{

	// Foward Declarations
	class Camera;
	class DrawProgram;
	class Texture;
	class TextureAtlas;
	class Input;

	class Graphics : public GameSystem
	{
	public:
		// Public Member Variables

		// The main camera
		Camera* mainCamera_;
	private:
		// Private Class Variables

		int windowWidth_ = 0, windowHeight_ = 0;
		int openGLVersionMajor_ = 0, openGLVersionMinor_ = 0;
		unsigned int vao_ = 0, vbo_ = 0;
		unsigned int renderJobBuffer_;
		
		// Texture array
		Texture* textureBank_;
		// Let the jank ensue (texture atlas)
		TextureAtlas* atlas_;

		GLFWwindow* windowHandle_ = nullptr;
		DrawProgram* defaultProgram_ = nullptr;
		Mat3 orthographicMatrix_;

		std::vector<RenderJob*> renderJobs_;
		std::vector<RenderJob> readyToRenderJobs_;
		
		// Private Member Functions
		// Hidden Constructors and Assigment Operators
		Graphics();
		Graphics(const Graphics& graphics);
		Graphics& operator=(const Graphics& other);
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

		// Returns: The window's with
		int GetWindowWidth() const;
		// Returns: The window's height
		int GetWindowHeight() const;
		// Gets a new render job from the memory manager of the graphics instance
		// Returns: A new pointer to the render job
		RenderJob* GetNewRenderJob();
		// Returns: The texture atlas
		TextureAtlas* GetTextureAtlas();
		// Removes a RenderJob from the list of rendering
		// Params:
		//	renderJob: The render job to remove
		void RemoveRenderJob(RenderJob* renderJob);
		// Returns: The singleton instance of this class
		static Graphics& GetInstance();
	};

	// The function callback that changes the viewport
	// Params:
	//	window: The window that is being resized
	//	width: The new width of the window
	//	height: The new height of the window
	void WindowResizeCallback(GLFWwindow* window, int width, int height);

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

	// Callbacak function when GL fires an error
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