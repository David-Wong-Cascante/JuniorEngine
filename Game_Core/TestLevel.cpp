/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: TestLevel.cpp
* Description: Test level for object management
* Created: 20 Dec 2018
* Last Modified: 7 July 2019
*/

// Includes
#include "TestLevel.h"

#ifdef _DEBUG
#include "MemoryLeakGuard.h"		// Memory Leak Guard
#endif
#include <GameObject.h>				// Game Object
#include <GameObjectManager.h>		// Game Object Manager
#include <GameObjectFactory.h>		// Game Object Factory
#include <Time.h>					// Time
#include <Input.h>					// Input
#include <Physics.h>				// Physics
#include <Transform.h>				// Transform
#include <Graphics.h>				// Graphics
#include <RenderJob.h>				// RenderJob
#include <Sprite.h>					// Sprite
#include <Animator.h>				// Animator
#include <Camera.h>					// Camera

Junior::TestLevel::TestLevel()
	: Level("TestLevel"), cog_(nullptr), cog2_(nullptr), transform_(nullptr), transform2_(nullptr), timer_(0.0), deletedObject2_(false), playerJoystick_(nullptr),
	lerpJoystickPosition(0, 0, 0)
{
}

bool Junior::TestLevel::Load()
{
	return true;
}

bool Junior::TestLevel::Initialize()
{
	GameObjectFactory::GetInstance().FillLevel("TestLevel");

	/*camera_ = GameObjectFactory::GetInstance().CreateObject("Camera");
	cog_ = GameObjectFactory::GetInstance().CreateObject("New Object");
	cog2_ = GameObjectFactory::GetInstance().CreateObject("Second New Object");*/

	camera_ = GameObjectManager::GetInstance().FindByName("Camera");
	cog_ = GameObjectManager::GetInstance().FindByName("New_Object");
	cog2_ = GameObjectManager::GetInstance().FindByName("Second_New_Object");

	cog_->AddChild(GameObjectManager::GetInstance().FindByName("Particle_Effect"));

	Camera* cameraComponent = camera_->GetComponent<Camera>();
	Graphics::GetInstance().mainCamera_ = cameraComponent;

	transform_ = cog_->GetComponent<Transform>();
	transform2_ = cog2_->GetComponent<Transform>();
	cameraTransform_ = camera_->GetComponent<Transform>();

	playerPhysics_ = cog_->GetComponent<Physics>();

	return true;
}

void Junior::TestLevel::Update(double dt)
{
	Input& input = Input::GetInstance();
	playerJoystick_ = input.GetJoystickState(GLFW_JOYSTICK_1);
	Animator* animator = cog_->GetComponent<Animator>();
	if (playerJoystick_)
	{
		if (playerJoystick_->axes_[0] < -0.7f)
		{
			playerPhysics_->SetVelocity(playerJoystick_->axes_[0] * Vec3(300, 0, 0));
			transform_->SetLocalScaling({ -128, 128, 1 });
			if(!animator->IsPlaying())
				animator->Play(0, 3, 0.15f, true);
		}
		else if (playerJoystick_->axes_[0] > 0.7f)
		{
			playerPhysics_->SetVelocity(playerJoystick_->axes_[0] * Vec3(300, 0, 0));
			transform_->SetLocalScaling({ 128, 128, 1 });
			if(!animator->IsPlaying())
				animator->Play(0, 3, 0.15f, true);
		}
		else
		{
			playerPhysics_->SetVelocity(Vec3());
			animator->Stop();
			animator->SetFrame(0);
		}
	}
	else
	{
		if (input.GetKeyState(GLFW_KEY_A))
		{
			playerPhysics_->SetVelocity(Vec3(-300, 0, 0));
			transform_->SetLocalScaling({ -128, 128, 1 });
			if (!animator->IsPlaying())
				animator->Play(0, 3, 0.15f, true);
		}
		else if (input.GetKeyState(GLFW_KEY_D))
		{
			playerPhysics_->SetVelocity(Vec3(300, 0, 0));
			transform_->SetLocalScaling({ 128, 128, 1 });
			if (!animator->IsPlaying())
				animator->Play(0, 3, 0.15f, true);
		}
		else
		{
			playerPhysics_->SetVelocity(Vec3());
			animator->Stop();
			animator->SetFrame(0);
		}
	}

	//transform_->SetLocalRotation(transform_->GetLocalRotation() + static_cast<float>(dt));
	transform2_->SetLocalTranslation(
		Junior::Vec3(300.0f * cosf(static_cast<float>(Junior::Time::GetInstance().GetTimeRan())), -300.0f , sinf(static_cast<float>(Junior::Time::GetInstance().GetTimeRan())))
	);

	// Slowly move the camera toward the player
	Vec3 toPlayer = transform_->GetLocalTranslation() - cameraTransform_->GetLocalTranslation();
	cameraTransform_->SetLocalTranslation(cameraTransform_->GetLocalTranslation() + toPlayer * 0.05f);

	/*if (!deletedObject2_)
	{
		timer_ += dt;
		if (timer_ >= 3.0)
		{
			deletedObject2_ = true;
			cog2_->Destroy();
		}
	}*/
}

void Junior::TestLevel::Shutdown()
{
	//GameObjectFactory::GetInstance().SaveLevel(this);
}

void Junior::TestLevel::Unload()
{
}