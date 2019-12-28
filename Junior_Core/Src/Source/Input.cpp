/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Input.cpp
* Description: Write the way our engine will handle user input
* Created: 20 Apr 2018
* Last Modified: 8 Aug 2019
*/

// Includes //
#include "Input.h"

#include <iostream>				// IO Stream
#include <string>				// Strings
#include <Debug.h>				// Debug
#include <EventManager.h>		// Event Manager

#include "OpenGLBundle.h"		// GLFW Bindings

// Forward Declarations

void Junior::JoystickConnectionCallback(int joystick, int state);

// Public Static Declarations

std::string Junior::KeyEvent::KeyEventName = "KeyEvent";

Junior::Input::Input()
	: GameSystem("Input"), keys(), mouseButtons(), joystickData(), cursorXPos(0.0), cursorYPos(0.0), scrollXOffset(0.0), scrollYOffset(0.0)
{
}

// Public Member Functions

int Junior::Input::GetKeyState(int key)
{
	std::map<int, int>::iterator keyFound = Input::keys.find(key);

	if (keyFound == Input::keys.end())
	{
		return 0;
	}

	return Input::keys[key];
}

int Junior::Input::GetMouseButtonState(int button)
{
	std::map<int, int>::iterator buttonFound = Input::mouseButtons.find(button);
	
	if (buttonFound == Input::mouseButtons.end())
	{
		return 0;
	}

	return Input::mouseButtons[button];
}

const Junior::JoystickData* Junior::Input::GetJoystickState(int id)
{
	// Search through the entire joystick list to find the one with the correct id
	auto end = joystickData.cend();
	for (auto begin = joystickData.cbegin(); begin < end; ++begin)
	{
		// Update the joystick
		JoystickData* data = *begin;
		data->axes_ = glfwGetJoystickAxes(data->id_, &data->axesCount_);
		data->buttons_ = glfwGetJoystickButtons(data->id_, &data->buttonCount_);
		return data;
	}

	return nullptr;
}

bool Junior::Input::Load()
{
	// TODO: Evenntually make joystick initialization more efficient
	// Kind of slow but functional addition of joystick
	for (unsigned joystick = GLFW_JOYSTICK_1; joystick <= GLFW_JOYSTICK_LAST; ++joystick)
	{
		bool present = glfwJoystickPresent(joystick);
		if (present)
		{
			JoystickConnectionCallback(joystick, GLFW_CONNECTED);
		}
		else
		{
			// There are no more joysticks to look for, quit early
			return true;
		}
	}

	return true;
}

bool Junior::Input::Initialize()
{
	return true;
}

void Junior::Input::Update(double dt)
{
}

void Junior::Input::Render()
{
}

void Junior::Input::Shutdown()
{

}

void Junior::Input::Unload()
{
	// Delete the leftover joysticks
	auto end = joystickData.end();
	for (auto begin = joystickData.begin(); begin < end; ++begin)
	{
		delete *begin;
	}

	joystickData.clear();
}

Junior::Input& Junior::Input::GetInstance()
{
	static Input input;
	return input;
}

// Global Functions

void Junior::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Check to see if the key exists in the map
	// If not, then create an entry for it
	Input& input = Input::GetInstance();
	std::map<int, int>::iterator searchedKey = input.keys.find(key);
	if (searchedKey == input.keys.end())
	{
		searchedKey = input.keys.begin();
		input.keys.insert(searchedKey, std::pair<int, int>(key, action));
	}

	// Send the event to the event manager
	KeyEvent* keyEvent = new KeyEvent;
	keyEvent->key_ = key;
	keyEvent->action_ = action;
	EventManager::GetInstance().SendEvent(keyEvent);

	// Update the key's state
	input.keys[key] = action;
}

void Junior::MouseButtonCallback(GLFWwindow* window, int button, int action, int mode)
{
	// Check to see if the button exists in the map
	// If not, then create an entry for it
	Input& input = Input::GetInstance();
	std::map<int, int>::iterator searchedButton = input.mouseButtons.find(button);
	if (searchedButton == input.mouseButtons.end())
	{
		searchedButton = input.mouseButtons.begin();
		input.mouseButtons.insert(searchedButton, std::pair<int, int>(button, action));
	}

	// Update the button's state
	input.mouseButtons[button] = action;
}

void Junior::MouseCursorCallback(GLFWwindow* window, double xPos, double yPos)
{
	Input& input = Input::GetInstance();
	input.cursorXPos = xPos;
	input.cursorYPos = yPos;
}

void Junior::MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	Input& input = Input::GetInstance();
	input.scrollXOffset += xOffset;
	input.scrollYOffset += yOffset;
}

void Junior::JoystickConnectionCallback(int joystick, int event)
{
	Input& input = Input::GetInstance();
	Debug& debug = Debug::GetInstance();

	switch (event)
	{
		// If the joystick got connected, then we need to create a new joystick struct and fit it inside the joystick list
	case GLFW_CONNECTED:
	{
		JoystickData* data = new JoystickData;
		data->id_ = joystick;
		data->axes_ = glfwGetJoystickAxes(joystick, &data->axesCount_);
		data->buttons_ = glfwGetJoystickButtons(joystick, &data->buttonCount_);
		data->name_ = glfwGetJoystickName(joystick);
		// Assign the joystick to the joystick list
		input.joystickData.push_back(data);
		// Debug print
#ifdef _DEBUG
		debug.Print("Connected Joystick ");
		debug.Print(data->name_);
		debug.Print(" (");
		debug.Print(joystick);
		debug.PrintLn(")");
#endif
		break;
	}
	// If the joystick got disconnected, then we need to delete it from our list
	case GLFW_DISCONNECTED:
		// Search for our joystick and delete it
		auto end = input.joystickData.end();
		for (auto begin = input.joystickData.begin(); begin < end; ++begin)
		{
			if ((*begin)->id_ == joystick)
			{
				// Debug print the disconnected
#ifdef _DEBUG
				debug.Print("Disconnected Joystick: ");
				debug.PrintLn(joystick);
#endif
				// Delete it
				delete *begin;
				input.joystickData.erase(begin);
				return;
			}
		}
		break;
	}
}