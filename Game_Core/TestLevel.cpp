/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: TestLevel.cpp
* Description: Test level for object management
* Created: 20 Dec 2018
* Last Modified: 28 Jul 2019
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

JuniorGame::TestLevel::TestLevel()
	: Level("TestLevel"), cog_(nullptr), cog2_(nullptr), transform_(nullptr), transform2_(nullptr), timer_(0.0), deletedObject2_(false)
{
}

bool JuniorGame::TestLevel::Load()
{
	return true;
}

bool JuniorGame::TestLevel::Initialize()
{
	Junior::GameObjectFactory::GetInstance().FillLevel("TestLevel");

	/*camera_ = GameObjectFactory::GetInstance().CreateObject("Camera");
	cog_ = GameObjectFactory::GetInstance().CreateObject("New Object");
	cog2_ = GameObjectFactory::GetInstance().CreateObject("Second New Object");*/

	camera_ = Junior::GameObjectManager::GetInstance().FindByName("Camera");
	cog_ = Junior::GameObjectManager::GetInstance().FindByName("Player");
	cog2_ = Junior::GameObjectManager::GetInstance().FindByName("Second_New_Object");

	cog_->AddChild(Junior::GameObjectManager::GetInstance().FindByName("Particle_Effect"));

	Junior::Camera* cameraComponent = camera_->GetComponent<Junior::Camera>();
	Junior::Graphics::GetInstance().mainCamera_ = cameraComponent;

	transform_ = cog_->GetComponent<Junior::Transform>();
	transform2_ = cog2_->GetComponent<Junior::Transform>();
	cameraTransform_ = camera_->GetComponent<Junior::Transform>();

	playerPhysics_ = cog_->GetComponent<Junior::Physics>();

	return true;
}

void JuniorGame::TestLevel::Update(double dt)
{
	//transform_->SetLocalRotation(transform_->GetLocalRotation() + static_cast<float>(dt));
	transform2_->SetLocalTranslation(
		Junior::Vec3(300.0f * cosf(static_cast<float>(Junior::Time::GetInstance().GetTimeRan())), -300.0f ,
					sinf(static_cast<float>(Junior::Time::GetInstance().GetTimeRan())))
	);

	// Slowly move the camera toward the player
	Junior::Vec3 toPlayer = transform_->GetLocalTranslation() - cameraTransform_->GetLocalTranslation();
	cameraTransform_->SetLocalTranslation(cameraTransform_->GetLocalTranslation() + toPlayer * 0.05f);
}

void JuniorGame::TestLevel::Shutdown()
{
}

void JuniorGame::TestLevel::Unload()
{
}