/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Input.cpp
* Description: Write the way our engine will handle user input
* Created: 20-Apr-2018
* Last Modified: 24-Apr-2018
*/

// Includes //
#include "Input.h"

#include <iostream>
#include <string>

#include "OpenGLBundle.h"

// Public Static Class Definitions //
std::map<int, int> Junior::Input::keys = std::map<int, int>();
std::map<int, int> Junior::Input::mouseButtons = std::map<int, int>();
std::vector<Junior::JoystickData*> Junior::Input::joystickData = std::vector<Junior::JoystickData*>();

double Junior::Input::cursorXPos = 0.0;
double Junior::Input::cursorYPos = 0.0;

double Junior::Input::scrollXOffset = 0.0;
double Junior::Input::scrollYOffset = 0.0;

// Global Functions //

void Junior::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Check to see if the key exists in the map
	// If not, then create an entry for it
	std::map<int, int>::iterator searchedKey = Input::keys.find(key);
	if (searchedKey == Input::keys.end())
	{
		searchedKey = Input::keys.begin();
		Input::keys.insert(searchedKey, std::pair<int, int>(key, action));
	}

	// Update the key's state
	Input::keys[key] = action;
}

void Junior::MouseButtonCallback(GLFWwindow* window, int button, int action, int mode)
{
	// Check to see if the button exists in the map
	// If not, then create an entry for it
	std::map<int, int>::iterator searchedButton = Input::mouseButtons.find(button);
	if (searchedButton == Input::mouseButtons.end())
	{
		searchedButton = Input::mouseButtons.begin();
		Input::mouseButtons.insert(searchedButton, std::pair<int, int>(button, action));
	}

	// Update the button's state
	Input::mouseButtons[button] = action;
}

void Junior::MouseCursorCallback(GLFWwindow* window, double xPos, double yPos)
{
	Input::cursorXPos = xPos;
	Input::cursorYPos = yPos;
}

void Junior::MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	Input::scrollXOffset += xOffset;
	Input::scrollYOffset += yOffset;
}

void Junior::JoystickConnectionCallback(int joystick, int event)
{
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
		Junior::Input::joystickData.push_back(data);
		// Debug print
#ifdef _DEBUG
		std::cout << "Connnected Joystick: " << data->name_ << "(" << joystick << ")" << std::endl;
#endif
		break;
	}
	// If the joystick got disconnected, then we need to delete it from our list
	case GLFW_DISCONNECTED:
		// Search for our joystick and delete it
		auto end = Junior::Input::joystickData.end();
		for (auto begin = Junior::Input::joystickData.begin(); begin < end; ++begin)
		{
			if ((*begin)->id_ == joystick)
			{
				// Debug print the disconnected
#ifdef _DEBUG
				std::cout << "Disconnected Joystick: " << joystick << std::endl;
#endif
				// Delete it
				delete *begin;
				Junior::Input::joystickData.erase(begin);
				return;
			}
		}
		break;
	}
}

// Public Member Functions //
int Junior::Input::GetKeyState(int key)
{
	std::map<int, int>::iterator keyFound = Input::keys.find(key);

	if (keyFound == Input::keys.end())
	{
		return -1;
	}

	return Input::keys[key];
}

int Junior::Input::GetMouseButtonState(int button)
{
	std::map<int, int>::iterator buttonFound = Input::mouseButtons.find(button);
	
	if (buttonFound == Input::mouseButtons.end())
	{
		return -1;
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

void Junior::Input::Load()
{
	// TODO: Evenntually make joystick initialization more efficient
	// Kind of slow but functional addition of joystick
	for (unsigned joystick = GLFW_JOYSTICK_1; joystick <= GLFW_JOYSTICK_LAST; ++joystick)
	{
		bool present = glfwJoystickPresent(joystick);
		if (present)
		{
			Junior::JoystickConnectionCallback(joystick, GLFW_CONNECTED);
		}
		else
		{
			// There are no more joysticks to look for, quit early
			return;
		}
	}
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