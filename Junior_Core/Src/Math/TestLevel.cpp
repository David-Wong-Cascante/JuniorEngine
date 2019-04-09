/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: TestLevel.cpp
* Description: Test level for object management
* Created: 20-Dec-2018
* Last Modified: 8-Apr-2018
*/

// Includes
#include "TestLevel.h"

#ifdef _DEBUG
#include "MemoryLeakGuard.h"		// Memory Leak Guard
#endif
#include "GameObject.h"				// Game Object
#include "GameObjectManager.h"		// Game Object Manager
#include "Time.h"					// Time
#include "Input.h"					// Input
#include "Transform.h"				// Transform
#include "Graphics.h"				// Graphics
#include "RenderJob.h"				// RenderJob
#include "Sprite.h"					// Sprite
#include "Animator.h"				// Animator
#include "Camera.h"					// Camera

Junior::TestLevel::TestLevel()
	: Level("TestLevel"), cog_(nullptr), cog2_(nullptr), transform_(nullptr), transform2_(nullptr), timer_(0.0), deletedObject2_(false), playerJoystick_(nullptr),
	lerpJoystickPosition(0, 0, 0)
{
}

bool Junior::TestLevel::Load()
{
	cog_ = new Junior::GameObject("New Object");
	cog2_ = new Junior::GameObject("Second New Object");
	camera_ = new Junior::GameObject("Camera", false);

	return cog_ && cog2_ && camera_;
}

bool Junior::TestLevel::Initialize()
{
	Camera* cameraComponent = new Junior::Camera;
	camera_->AddComponent(cameraComponent);
	Graphics& graphics = Graphics::GetInstance();
	cameraComponent->UpdateProjection(ProjectionMode::ORTHOGRAPHIC, static_cast<float>(graphics.GetWindowWidth()), 
										static_cast<float>(graphics.GetWindowHeight()), -5.0f, 5.0f);

	Transform* transform = new Junior::Transform;
	cog_->AddComponent(transform);
	cog2_->AddComponent(new Junior::Transform);
	camera_->AddComponent(new Junior::Transform);

	cog_->AddComponent(new Sprite("..//Assets//Images//GoldenAnim.png"));
	cog2_->AddComponent(new Sprite("..//Assets//Images//WideTestImage1.png"));

	Graphics::GetInstance().mainCamera_ = cameraComponent;

	Animator* animator = new Animator(2, 4);
	cog_->AddComponent(animator);
	transform_ = cog_->GetComponent<Transform>();
	transform2_ = cog2_->GetComponent<Transform>();
	cameraTransform_ = camera_->GetComponent<Transform>();

	if (!transform_ || !transform2_)
	{
		return false;
	}

	transform_->SetLocalTranslation(Vec3(-.25f, 0.f, 0.0));
	transform_->SetLocalScaling({ 128, 128, 1 });
	transform2_->SetLocalTranslation(Vec3(300.0f, 0.0f, 0.0f));
	transform2_->SetLocalScaling(Vec3(256, 128, 1));

	cog_->GetRenderJob()->textureID_ = 0;
	cog2_->GetRenderJob()->textureID_ = 0;
	// Set the a child to the first game object

	// Add the components
	Junior::GameObjectManager::GetInstance().AddObject(cog_);
	Junior::GameObjectManager::GetInstance().AddObject(cog2_);
	Junior::GameObjectManager::GetInstance().AddObject(camera_);

	return true;
}

void Junior::TestLevel::Update(double dt)
{
	Input& input = Input::GetInstance();
	playerJoystick_ = input.GetJoystickState(GLFW_JOYSTICK_1);
	Animator* animator = cog_->GetComponent<Animator>();
	if (playerJoystick_)
	{
		if (playerJoystick_->axes_[0] < -0.2f)
		{
			transform_->SetLocalTranslation(transform_->GetLocalTranslation() + Vec3(300.0f * playerJoystick_->axes_[0], 0, 0) * static_cast<float>(dt));
			transform_->SetLocalScaling({ -128, 128, 1 });
			if(!animator->IsPlaying())
				animator->Play(0, 3, 0.15f, true);
		}
		else if (playerJoystick_->axes_[0] > 0.7f)
		{
			transform_->SetLocalTranslation(transform_->GetLocalTranslation() + Vec3(300.0f* playerJoystick_->axes_[0], 0, 0) * static_cast<float>(dt));
			transform_->SetLocalScaling({ 128, 128, 1 });
			if(!animator->IsPlaying())
				animator->Play(0, 3, 0.15f, true);
		}
		else
		{
			animator->Stop();
			animator->SetFrame(0);
		}
	}
	else
	{
		if (input.GetKeyState(GLFW_KEY_A))
		{
			transform_->SetLocalTranslation(transform_->GetLocalTranslation() + Vec3(-300.0f, 0, 0) * static_cast<float>(dt));
			transform_->SetLocalScaling({ -128, 128, 1 });
			if (!animator->IsPlaying())
				animator->Play(0, 3, 0.15f, true);
		}
		else if (input.GetKeyState(GLFW_KEY_D))
		{
			transform_->SetLocalTranslation(transform_->GetLocalTranslation() + Vec3(300.0f, 0, 0) * static_cast<float>(dt));
			transform_->SetLocalScaling({ 128, 128, 1 });
			if (!animator->IsPlaying())
				animator->Play(0, 3, 0.15f, true);
		}
		else
		{
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
	cameraTransform_->SetLocalTranslation(cameraTransform_->GetLocalTranslation() + toPlayer * 0.1f);

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

void Junior::TestLevel::Unload()
{
}