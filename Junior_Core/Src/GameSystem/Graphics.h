#pragma once
/* 
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * File name: Graphics.h
 * Description: Declare the functionality of the window and the renderer under the same class
 * Created: 20-Apr-2018
 * Last Modified: 29-Oct-2018
*/

// Includes //
#include <vector>			// Vector
#include "Mat3.h"			// Mat3
#include "GameSystem.h"		// Game System

struct GLFWwindow;
namespace Junior
{

	// Foward Declarations //
	class Texture;
	class DrawProgram;
	class Input;
	struct RenderJob;

	class Graphics : public GameSystem
	{
	private:
		// Private Class Variables //
		int windowWidth_ = 0, windowHeight_ = 0;
		unsigned int vao_ = 0, vbo_ = 0;
		unsigned int transformationBuffer_ = 0;
		
		// Texture array
		Texture* textureBank_;

		std::vector<Mat3> renderJobTransformations_;

		GLFWwindow* windowHandle_ = nullptr;
		DrawProgram* defaultProgram_ = nullptr;
		std::vector<RenderJob*> renderJobs_;
		Mat3 orthographicMatrix_;
		
		// Private Member Functions
	public:
		// Public Member Functions
		// The Constructor of the Game Engine
		Graphics();
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
		// Sets the dimensions of the window
		// Params:
		//	width: the width of the screen
		//	height: the height of the screen
		void SetDimensions(int width, int height);
		// Poll the window so it actually responds
		void PollWindow();

		// Gets a new render job from the memory manager of the graphics instance
		// Returns: A new pointer to the render job
		RenderJob* GetNewRenderJob();
		// Removes a RenderJob from the list of rendering
		// Params:
		//	renderJob: The render job to remove
		void RemoveRenderJob(RenderJob* renderJob);
		// Returns: The singleton instance of this class
		static Graphics& GetInstance();
	};

	// The function callback that changes the viewport
	void WindowResizeCallback(GLFWwindow* window, int width, int height);
}