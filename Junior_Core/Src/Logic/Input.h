#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Input.h
* Description: Declare the way our engine will handle user input
* Created: 20-Apr-2018
* Last Modified: 29-Oct-2018
*/

// Includes //
#include <map>						// std::map

// Forward Declarations //
struct GLFWwindow;

namespace Junior
{
	class Input
	{
	public:
		// Public Class Variables //
		static std::map<int, int> keys;
		static std::map<int, int> mouseButtons;
		static double cursorXPos, cursorYPos;
		static double scrollXOffset, scrollYOffset;
		// Public Member Functions //
		int static GetKeyState(int);
		int static GetMouseButtonState(int);
	};

	// Global Functions //
	// Set the Keyboard callback that GLFW uses to report user key input
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mode);
	void MouseCursorCallback(GLFWwindow* window, double xPos, double yPos);
	void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
}