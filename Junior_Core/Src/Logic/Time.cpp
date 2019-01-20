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

#include "OpenGLBundle.h"				// Get GLFW time functionality

Junior::Time::Time()
	: GameSystem("Time"), prevTime_(0.0), currTime_(0.0), timeRan_(0.0), deltaTime_(0.0), scaledDeltaTime_(0.0), timeScale_(1.0)
{

}

// Public Member Functions //
bool Junior::Time::Load()
{
	return true;
}

bool Junior::Time::Initialize()
{
	timeScale_ = 1.0;
	return true;
}

void Junior::Time::Render()
{

}

void Junior::Time::Update(double)
{
	prevTime_ = currTime_;
	currTime_ = glfwGetTime();
	timeRan_ = glfwGetTime();
	deltaTime_ = currTime_ - prevTime_;
	scaledDeltaTime_ = deltaTime_ * timeScale_;
}

void Junior::Time::Shutdown()
{

}

void Junior::Time::Unload()
{

}

// Mutators
void Junior::Time::SetTimeScale(double timeScale)
{
	timeScale_ = timeScale;
}

// Accessors
double Junior::Time::GetDeltaTime() const
{
	return deltaTime_;
}

double Junior::Time::GetScaledDeltaTime() const
{
	return scaledDeltaTime_;
}

double Junior::Time::GetTimeRan() const
{
	return timeRan_;
}

double Junior::Time::GetTimeScale() const
{
	return timeScale_;
}

Junior::Time& Junior::Time::GetInstance()
{
	static Time time;
	return time;
}
