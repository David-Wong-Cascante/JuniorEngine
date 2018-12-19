/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: main.cpp
* Description: Starts up the program
* Created: 11-Dec-2018
* Last Modified: 18-Dec-2018
*/

#include <iostream>							// IO Stream
#include <string>							// String
#include <math.h>							// Math

#include "Graphics.h"						// Graphics
#include "Vec3.h"							// Vec3
#include "Mat3.h"							// Mat3
#include "Time.h"							// Time
#include "GameObject.h"						// Game Object
#include "Transform.h"						// Transform
#include "LinearMath.h"						// Linear Math
#include "Input.h"							// Input
#include "MemoryManager.h"					// Memory Manager
#include "GameObjectManager.h"				// Game Object Manager
#include "OpenGLBundle.h"					// OpenGL

int main(void)
{
	// Initialize the memory manager for everything else in the game engine
	Junior::MemoryManager manager;
	// Create the Graphics class
	Junior::Graphics& g = static_cast<Junior::Graphics&>(Junior::Graphics::GetInstance());
	// Initialize the containers for the keys and the mouse buttons
	Junior::Input::keys = std::map<int, int>();
	Junior::Input::mouseButtons = std::map<int, int>();
	
	// Load the Graphics class
	if (!g.Load())
	{
		return -1;
	}
	// Initialize the Graphics class
	if (!g.Initialize())
	{
		return -1;
	}

	Junior::GameObject* cog = new Junior::GameObject("New Object");
	Junior::GameObject* cog2 = new Junior::GameObject("Second New Object");

	cog->AddComponent(new Junior::Transform(&g));
	cog2->AddComponent(new Junior::Transform(&g));

	Junior::Transform* transform = (Junior::Transform*)cog->GetComponent(Junior::ComponentType::TRANSFORM);
	Junior::Transform* transform2 = (Junior::Transform*)cog2->GetComponent(Junior::ComponentType::TRANSFORM);
	
	transform->SetLocalTranslation(Junior::Vec3(-.25f, 0.f, 0.f ));
	transform->SetLocalScaling({ 300, 300, 1 });
	transform2->SetLocalTranslation(Junior::Vec3(300.0f, 0.0f, 0.0f));
	transform2->SetLocalScaling(Junior::Vec3(0.5f, 0.5f, 1));

	// Set the a child to the first game object
	cog->AddChild(cog2);

	// Add the components
	Junior::GameObjectManager::GetInstance().AddObject(cog);
	Junior::GameObjectManager::GetInstance().AddObject(cog2);

	// Test deletion
	bool deletedObject2 = false;
	double timer = 0.0;

	// Create the game loop
	while (!g.WindowRequestClosed())
	{
		// Update all of the time functions
		Junior::Time::Update();
		// Quit the game loop if the user presses escape
		if (Junior::Input::GetKeyState(GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			break;
		}

		transform->SetLocalRotation(transform->GetLocalRotation() + static_cast<float>(Junior::Time::deltaTime));
		transform->SetLocalTranslation(Junior::Vec3(0, 300.0f * sinf(static_cast<float>(Junior::Time::timeRan)), 0));
		transform2->SetLocalTranslation(
			Junior::Vec3(cosf(static_cast<float>(Junior::Time::timeRan)), 0, sinf(static_cast<float>(Junior::Time::timeRan)))
		);
		
		timer += Junior::Time::deltaTime;
		if (!deletedObject2 && timer >= 3.0)
		{
			deletedObject2 = true;
			cog2->Destroy();
		}

		Junior::GameObjectManager::GetInstance().Update(&manager);

		// Update the graphics
		g.Render();
		g.PollWindow();
	}

	Junior::GameObjectManager::GetInstance().CleanUp(&manager);
	//
	//manager.DeAllocate(cog);
	//manager.DeAllocate(cog2);

	delete cog;
	delete cog2;

	g.Shutdown();
	g.Unload();

	//std::cin.get();

	return 0;
}