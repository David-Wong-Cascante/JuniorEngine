/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: GameObjectFactory.cpp
* Description: Constructs game objects and components from files
* Created: 9-Apr-2019
* Last Modified: 9-Apr-2019
*/

// Includes
#include "GameObjectFactory.h"			// Game Object Factory
#include "ComponentContainer.h"			// Component Container
#include "GameObject.h"					// Game Object
#include "Debug.h"						// Debug
// Includes for all the standard components
#include "Transform.h"
#include "Sprite.h"
#include "Animator.h"
#include "Camera.h"

// Defines
#define NUM_STANDARD_COMPONENTS 4

// Private Member Functions

Junior::GameObjectFactory::GameObjectFactory()
	: preparedComponents(), filePath("..//Assets//Objects//"), fileExtension(".juo")
{
	preparedComponents.reserve(NUM_STANDARD_COMPONENTS);
	RegisterComponent<Transform>();
	RegisterComponent<Sprite>();
	RegisterComponent<Animator>();
	RegisterComponent<Camera>();
}

Junior::GameObjectFactory::~GameObjectFactory()
{
	// Delete all of the prepared components
	for (auto cbegin = preparedComponents.cbegin(); cbegin < preparedComponents.cend(); ++cbegin)
	{
		(*cbegin)->Unload();
		delete (*cbegin);
	}

	preparedComponents.clear();
}

Junior::ComponentContainer* Junior::GameObjectFactory::CreateComponent(const std::string& name) const
{
	// Traverse the entirety of the prepared components list and find the one with the correct name
	for (auto cbegin = preparedComponents.cbegin(); cbegin < preparedComponents.cend(); ++cbegin)
	{
		// If we found the component we were looking for, then we need to clone it and return it
		if ((*cbegin)->GetTypeName() == name)
		{
			return (*cbegin)->Clone();
		}
	}
	return nullptr;
}

Junior::GameObject* Junior::GameObjectFactory::CreateObject(const std::string& name) const
{
	// Find the name of the game object first
	std::string objectName;
	Parser parser(filePath + name + fileExtension);
	parser.ReadValue(objectName);
	GameObject* gameObject = new GameObject(objectName);
	try
	{
		gameObject->Deserialize(parser);
	}
	catch (const ParserException& e)
	{
		Debug& debug = Debug::GetInstance();
		debug.Print(debug.GetDebugLevelName(DebugLevel::ERROR));
		debug.Print("Failed to deserialize game object \"" + objectName + "\": ");
		debug.PrintLn(e.what());
		delete gameObject;
	}
	return gameObject;
}

void Junior::GameObjectFactory::SaveObject(GameObject* archetype) const
{
	std::string objectName = archetype->GetName();
	Parser parser(filePath + objectName + fileExtension, std::ios::out);
	try
	{
		archetype->Serialize(parser);
	}
	catch (const ParserException& e)
	{
		Debug& debug = Debug::GetInstance();
		debug.Print(debug.GetDebugLevelName(DebugLevel::ERROR));
		debug.Print("Failed to serialize game object \"" + objectName + "\": ");
		debug.PrintLn(e.what());
	}
}

Junior::GameObjectFactory& Junior::GameObjectFactory::GetInstance()
{
	static GameObjectFactory instance;
	return instance;
}