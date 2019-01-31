/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: TestLevel.cpp
* Description: Test level for object management
* Created: 20-Dec-2018
* Last Modified: 20-Dec-2018
*/

// Includes
#include "TestLevel.h"

#include "MemoryLeakGuard.h"		// Memory Leak Guard
#include "GameObject.h"				// Game Object
#include "GameObjectManager.h"		// Game Object Manager
#include "Time.h"					// Time
#include "Input.h"					// Input
#include "Transform.h"				// Transform
#include "Graphics.h"				// Graphics
#include "RenderJob.h"				// RenderJob

Junior::TestLevel::TestLevel()
	: Level("TestLevel"), cog(nullptr), cog2_(nullptr), transform_(nullptr), transform2_(nullptr), timer_(0.0), deletedObject2_(false)
{
}

bool Junior::TestLevel::Load()
{
	cog = new Junior::GameObject("New Object");
	cog2_ = new Junior::GameObject("Second New Object");

	return cog && cog2_;
}

bool Junior::TestLevel::Initialize()
{
	cog->AddComponent(new Junior::Transform(&Graphics::GetInstance()));
	cog2_->AddComponent(new Junior::Transform(&Graphics::GetInstance()));

	transform_ = (Junior::Transform*)cog->GetComponent(Junior::ComponentType::TRANSFORM);
	transform2_ = (Junior::Transform*)cog2_->GetComponent(Junior::ComponentType::TRANSFORM);

	if (!transform_ || !transform2_)
	{
		return false;
	}

	transform_->SetLocalTranslation(Junior::Vec3(-.25f, 0.f, 0.f));
	transform_->SetLocalScaling({ 300, 300, 1 });
	transform2_->SetLocalTranslation(Junior::Vec3(300.0f, 0.0f, 0.0f));
	transform2_->SetLocalScaling(Junior::Vec3(0.5f, 0.5f, 1));

	transform_->GetRenderJob()->textureID_ = 1;
	transform2_->GetRenderJob()->textureID_ = 0;
	// Set the a child to the first game object
	cog->AddChild(cog2_);

	// Add the components
	Junior::GameObjectManager::GetInstance().AddObject(cog);
	Junior::GameObjectManager::GetInstance().AddObject(cog2_);

	return true;
}

void Junior::TestLevel::Update(double dt)
{
	transform_->SetLocalRotation(transform_->GetLocalRotation() + static_cast<float>(dt));
	transform_->SetLocalTranslation(Junior::Vec3(0, 300.0f * sinf(static_cast<float>(Junior::Time::GetInstance().GetTimeRan())), 0));
	transform2_->SetLocalTranslation(
		Junior::Vec3(cosf(static_cast<float>(Junior::Time::GetInstance().GetTimeRan())), 0, sinf(static_cast<float>(Junior::Time::GetInstance().GetTimeRan())))
	);

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