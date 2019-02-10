#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Input.h
* Description: Declare the way our engine will handle user input
* Created: 20-Apr-2018
* Last Modified: 9-Feb-2019
*/

// Includes //
#include "GameSystem.h"				// Game System
#include <map>						// std::map
#include <vector>					// std::vector

// Forward Declarations //
struct GLFWwindow;

namespace Junior
{
	// POD for Joysticks
	struct JoystickData
	{
		// Name
		const char* name_;
		// Button Count
		int buttonCount_;
		// Axes Count
		int axesCount_;
		// Axis states
		const float* axes_;
		// The joystick ID
		unsigned id_;
		// Button States
		const unsigned char* buttons_;
	};

	class Input : public GameSystem
	{
	private:
		// Private Class Variables //
		// The keys map
		static std::map<int, int> keys;
		// The mouse map
		static std::map<int, int> mouseButtons;
		// Joystick data
		static std::vector<JoystickData*> joystickData;
	public:
		// Public Class Variables //
		// Cursor X and Y Position
		static double cursorXPos, cursorYPos;
		// Scroll wheel
		static double scrollXOffset, scrollYOffset;
		// Public Member Functions //
		// Params:
		//	id: The key id
		// Returns: The Key's State
		int static GetKeyState(int id);
		// Params: 
		//	button: The mouse button
		// Returns: The state of the button
		int static GetMouseButtonState(int button);
		// Params:
		//	id: The joystick's id
		// Returns: The joystick's data, or nullptr if it can't find the correct joystick
		static const JoystickData* GetJoystickState(int id);
	
		// Inititalizes input components
		static void Load();
		// Unloads input components
		static void Unload();
		// Friend Functions
		friend void JoystickConnectionCallback(int joystick, int event);
		friend void MouseButtonCallback(GLFWwindow* window, int button, int action, int mode);
		friend void MouseCursorCallback(GLFWwindow* window, double xPos, double yPos);
		friend void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
		friend void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	};
}