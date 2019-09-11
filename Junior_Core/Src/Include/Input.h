#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Input.h
* Description: Declare the way our engine will handle user input
* Created: 20 Apr 2018
* Last Modified: 10 Sep 2019
*/

// Includes //
#include "GameSystem.h"				// Game System
#include "EventManager.h"			// Event Manager
#include "Event.h"					// Event
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

	// Event Structs for the Event Manager
	struct KeyEvent : public Event
	{
		// Public Member Variables

		// The key we are changing
		int key_;
		// How the key is being changed
		int action_;

		// Public Member Functions

		// Constructor
		KeyEvent()
			: Event(KeyEventName), key_(0), action_(0)
		{
		}

		// Public Static Variables

		// The name of the Key Event
		static std::string KeyEventName;
	};

	class Input : public GameSystem
	{
	private:
		// Private Class Variables //
		// The keys map
		std::map<int, int> keys;
		// The mouse map
		std::map<int, int> mouseButtons;
		// Joystick data
		std::vector<JoystickData*> joystickData;
	public:
		// Public Class Variables //

		// Constructor
		Input();
		// Cursor X and Y Position
		double cursorXPos, cursorYPos;
		// Scroll wheel
		double scrollXOffset, scrollYOffset;
		// Public Member Functions //
		// Params:
		//	id: The key id
		// Returns: The Key's State
		int GetKeyState(int id);
		// Params: 
		//	button: The mouse button
		// Returns: The state of the button
		int GetMouseButtonState(int button);
		// Params:
		//	id: The joystick's id
		// Returns: The joystick's data, or nullptr if it can't find the correct joystick
		const JoystickData* GetJoystickState(int id);
	
		// Loads the component
		// Returns: Whether input succeeded in loading
		bool Load() override;
		// Inititalizes input components
		// Returns: Whether input succeded in initializing
		bool Initialize() override;
		// Updates the component
		// Params:
		//	dt: Time between frames
		void Update(double dt) override;
		// Renders the input (useful for debug)
		void Render() override;
		// Shuts down the component
		void Shutdown() override;
		// Unloads input components
		void Unload() override;
		// Friend Functions
		friend void JoystickConnectionCallback(int joystick, int event);
		friend void MouseButtonCallback(GLFWwindow* window, int button, int action, int mode);
		friend void MouseCursorCallback(GLFWwindow* window, double xPos, double yPos);
		friend void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
		friend void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

		// Returns: A static instance of the input
		static Input& GetInstance();
	};
}