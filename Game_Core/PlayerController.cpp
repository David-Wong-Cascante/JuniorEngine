/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: PlayerController.cpp
* Description: Makes the player be able to move around
* Created: 28 Jul 2019
* Last Modified: 28 Jul 2019
*/

// Includes
#include "PlayerController.h"			// Player Controller

#include <GLFW/glfw3.h>					// GLFW for the key codes
#include <GameObject.h>					// Game Object
#include <Transform.h>					// Transform
#include <Physics.h>					// Physics
#include <Animator.h>					// Animator
#include <Input.h>						// Input

// Public Member Functions

JuniorGame::PlayerController::PlayerController()
{
}

JuniorGame::PlayerController::PlayerController(const JuniorGame::PlayerController& other)
{
}

void JuniorGame::PlayerController::Initialize()
{
	transform_ = owner_->GetComponent<Junior::Transform>();
	physics_ = owner_->GetComponent<Junior::Physics>();
	animator_ = owner_->GetComponent<Junior::Animator>();
}

void JuniorGame::PlayerController::Update(double dt)
{
	Junior::Input& input = Junior::Input::GetInstance();
	joystickData_ = input.GetJoystickState(GLFW_JOYSTICK_1);
	if (joystickData_)
	{
		if (joystickData_->axes_[0] < -0.7f)
		{
			physics_->SetVelocity(joystickData_->axes_[0] * Junior::Vec3(300, 0, 0));
			transform_->SetLocalScaling({ -128, 128, 1 });
			if (!animator_->IsPlaying())
				animator_->Play(0, 3, 0.15f, true);
		}
		else if (joystickData_->axes_[0] > 0.7f)
		{
			physics_->SetVelocity(joystickData_->axes_[0] * Junior::Vec3(300, 0, 0));
			transform_->SetLocalScaling({ 128, 128, 1 });
			if (!animator_->IsPlaying())
				animator_->Play(0, 3, 0.15f, true);
		}
		else
		{
			physics_->SetVelocity(Junior::Vec3());
			animator_->Stop();
			animator_->SetFrame(0);
		}
	}
	else
	{
		if (input.GetKeyState(GLFW_KEY_A))
		{
			physics_->SetVelocity(Junior::Vec3(-300, 0, 0));
			transform_->SetLocalScaling({ -128, 128, 1 });
			if (!animator_->IsPlaying())
				animator_->Play(0, 3, 0.15f, true);
		}
		else if (input.GetKeyState(GLFW_KEY_D))
		{
			physics_->SetVelocity(Junior::Vec3(300, 0, 0));
			transform_->SetLocalScaling({ 128, 128, 1 });
			if (!animator_->IsPlaying())
				animator_->Play(0, 3, 0.15f, true);
		}
		else
		{
			physics_->SetVelocity(Junior::Vec3());
			animator_->Stop();
			animator_->SetFrame(0);
		}
	}
}

void JuniorGame::PlayerController::Serialize(Junior::Parser& parser) const
{
}

void JuniorGame::PlayerController::Deserialize(Junior::Parser& parser)
{
}