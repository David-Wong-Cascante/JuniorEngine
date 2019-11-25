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
#include <Sprite.h>						// Sprite
#include <Texture.h>					// Texture

// Public Member Functions

JuniorGame::PlayerController::PlayerController()
	: animator_(nullptr), joystickData_(nullptr), physics_(nullptr), transform_(nullptr), sprite_(nullptr),
	  groundLevel_(-200.0f), gravity_(0, -1200.0f), jumpPower_(0.0f, 600.0f), spriteHalfHeight_(0.0f),
	  grounded_(false)
{
}

JuniorGame::PlayerController::PlayerController(const JuniorGame::PlayerController& other)
	: animator_(nullptr), joystickData_(nullptr), physics_(nullptr), transform_(nullptr), sprite_(nullptr),
	  groundLevel_(-200.0f), gravity_(0, -1200.0f), jumpPower_(0.0f, 600.0f), spriteHalfHeight_(0.0f),
	  grounded_(false)
{
}

void JuniorGame::PlayerController::Initialize()
{
	// Get the components
	transform_ = owner_->GetComponent<Junior::Transform>();
	physics_ = owner_->GetComponent<Junior::Physics>();
	animator_ = owner_->GetComponent<Junior::Animator>();
	sprite_ = owner_->GetComponent<Junior::Sprite>();
	// Get the sprite's half height
	spriteHalfHeight_ = sprite_->GetTexture()->GetDimension(1) / 2.0f;
}

void JuniorGame::PlayerController::Update(double dt)
{
	Junior::Input& input = Junior::Input::GetInstance();
	Junior::Vec3 vel, prevVel;

	// Only apply the gravity if the player is ground
	prevVel = physics_->GetVelocity();

	Junior::Vec3 translation = transform_->GetLocalTranslation();
	if ((translation.y_ - spriteHalfHeight_) < groundLevel_)
	{
		translation.y_ = groundLevel_ + spriteHalfHeight_;
		prevVel.y_ = 0.0f;
		transform_->SetLocalTranslation(translation);
		grounded_ = true;
	}
	else
	{
		prevVel += gravity_ * dt;
	}

	joystickData_ = input.GetJoystickState(GLFW_JOYSTICK_1);
	if (joystickData_)
	{
		if (joystickData_->axes_[0] < -0.5f)
		{
			vel = joystickData_->axes_[0] * Junior::Vec3(300, 0, 0);
		}
		else if (joystickData_->axes_[0] > 0.5f)
		{
			vel = joystickData_->axes_[0] * Junior::Vec3(300, 0, 0);
		}

		if (joystickData_->buttons_[0] == GLFW_PRESS && grounded_)
		{
			vel += jumpPower_;
			grounded_ = false;
		}
	}
	else
	{
		if (input.GetKeyState(GLFW_KEY_A))
		{
			vel -= Junior::Vec3(300, 0, 0);
		}

		if (input.GetKeyState(GLFW_KEY_D))
		{
			vel += Junior::Vec3(300, 0, 0);
		}

		if (input.GetKeyState(GLFW_KEY_SPACE) && grounded_)
		{
			vel += jumpPower_;
			grounded_ = true;
		}
	}

	if (vel.x_ > 0.0f)
	{
		transform_->SetLocalScaling({ 128, 128, 1 });
		if (!animator_->IsPlaying())
			animator_->Play(0, 3, 0.15f, true);
	}
	else if (vel.x_ < 0.0f)
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

	if (!grounded_)
	{
		animator_->Stop();
		animator_->SetFrame(5);
	}

	prevVel.x_ = vel.x_;
	prevVel.y_ += vel.y_;

	physics_->SetVelocity(prevVel);
}

void JuniorGame::PlayerController::Serialize(Junior::Parser& parser) const
{
}

void JuniorGame::PlayerController::Deserialize(Junior::Parser& parser)
{
}