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
