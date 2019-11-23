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
	: animator_(nullptr), joystickData_(nullptr), physics_(nullptr), transform_(nullptr)
{
}

JuniorGame::PlayerController::PlayerController(const JuniorGame::PlayerController& other)
	: animator_(nullptr), joystickData_(nullptr), physics_(nullptr), transform_(nullptr)
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
		if (joystickData_->axes_[0] < -0.5f)
		{
			physics_->SetVelocity(joystickData_->axes_[0] * Junior::Vec3(300, 0, 0));
			transform_->SetLocalScaling({ -128, 128, 1 });
			if (!animator_->IsPlaying())
				animator_->Play(0, 3, 0.15f, true);
		}
		else if (joystickData_->axes_[0] > 0.5f)
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
		Junior::Vec3 vel;
		if (input.GetKeyState(GLFW_KEY_A))
		{
			vel -= Junior::Vec3(300, 0, 0);
		}
		
		if (input.GetKeyState(GLFW_KEY_D))
		{
			vel += Junior::Vec3(300, 0, 0);
		}

		if (vel.x_ == 300)
		{
			transform_->SetLocalScaling({ 128, 128, 1 });
			if (!animator_->IsPlaying())
				animator_->Play(0, 3, 0.15f, true);
		}
		else if (vel.x_ == -300)
		{
			transform_->SetLocalScaling({ -128, 128, 1 });
			if (!animator_->IsPlaying())
				animator_->Play(0, 3, 0.15f, true);
		}
		else
		{
			animator_->Stop();
			animator_->SetFrame(0);
		}

		physics_->SetVelocity(vel);
	}
}

void JuniorGame::PlayerController::Serialize(Junior::Parser& parser) const
{
}

void JuniorGame::PlayerController::Deserialize(Junior::Parser& parser)
{
}