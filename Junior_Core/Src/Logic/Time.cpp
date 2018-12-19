/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Time.cpp
* Description: Declare the Time system for our engine
* Created: 27-Apr-2018
* Last Modified: 29-Oct-2018
*/

// Includes //
#include "Time.h"

// Get GLFW time functionality
#include "OpenGLBundle.h"

// Static Public Class Variables //
double Junior::Time::deltaTime = 0.0;
double Junior::Time::timeRan = 0.0;
double Junior::Time::timeScale = 1.0;
double Junior::Time::scaledDeltaTime = 0.0;
double Junior::Time::prevTime = 0.0;
double Junior::Time::currTime = 0.0;

// Static Public Member Functions //
void Junior::Time::Update()
{
	prevTime = currTime;
	currTime = glfwGetTime();
	timeRan = glfwGetTime();
	deltaTime = currTime - prevTime;
	scaledDeltaTime = deltaTime * timeScale;
}