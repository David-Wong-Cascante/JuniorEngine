/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: GameObjectFactory.cpp
* Description: Constructs game objects and components from files
* Created: 9 Apr 2019
* Last Modified: 2 Oct 2019
*/

// Includes
#include "GameObjectFactory.h"			// Game Object Factory
#include "GameObjectManager.h"			// Game Object Manager
#include "ComponentContainer.h"			// Component Container
#include "GameObject.h"					// Game Object
#include "Level.h"						// Level
#include "Space.h"						// Space
#include "Debug.h"						// Debug
// Includes for all the standard components
#include "Transform.h"
#include "Sprite.h"
#include "Animator.h"
#include "Camera.h"
#include "ParticleEmitter.h"
#include "DefaultMeshLink.h"
#include "ParticleMeshLink.h"
#include "Physics.h"

// Defines
#define NUM_STANDARD_COMPONENTS 8

// Private Member Functions

Junior::GameObjectFactory::GameObjectFactory()
	: filePath_("Assets//Objects//"), objectFileExtension_(".juo"), levelFileExtenion_(".jlv")
{
	preparedComponents_.reserve(NUM_STANDARD_COMPONENTS);
	RegisterComponent<Transform>();
	RegisterComponent<Sprite>();
	RegisterComponent<Animator>();
	RegisterComponent<Camera>();
	RegisterComponent<ParticleEmitter>();
	RegisterComponent<ParticleMeshLink>();
	RegisterComponent<DefaultMeshLink>();
	RegisterComponent<Physics>();
}

Junior::GameObjectFactory::~GameObjectFactory()
{
	// Delete all of the prepared components
	for (auto cbegin = preparedComponents_.cbegin(); cbegin < preparedComponents_.cend(); ++cbegin)
	{
		(*cbegin)->Unload();
		delete (*cbegin);
	}

	preparedComponents_.clear();
}

Junior::ComponentContainer* Junior::GameObjectFactory::CreateComponent(const std::string& name) const
{
	// Traverse the entirety of the prepared components list and find the one with the correct name
	for (auto cbegin = preparedComponents_.cbegin(); cbegin < preparedComponents_.cend(); ++cbegin)
	{
		// If we found the component we were looking for, then we need to clone it and return it
		if ((*cbegin)->GetTypeName() == name)
		{
			return (*cbegin)->Clone();
		}
	}
	return nullptr;
}

Junior::GameObject* Junior::GameObjectFactory::CreateObject(const std::string& name, bool asArchetype) const
{
	// Find the name of the game object first
	std::string objectName;
	Parser parser(filePath_ + name + objectFileExtension_, std::ios_base::in);
	parser.ReadValue(objectName);
	GameObject* gameObject = new GameObject(objectName, asArchetype);
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

void Junior::GameObjectFactory::SaveObject(const GameObject* archetype) const
{
	std::string objectName = archetype->GetName();
	Parser parser(filePath_ + objectName + objectFileExtension_, std::ios::out);
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

void Junior::GameObjectFactory::SaveLevel(const Level* level) const
{
	std::string levelName = level->GetName();
	Parser parser(filePath_ + levelName + levelFileExtenion_, std::ios_base::out);
	try
	{
		level->Serialize(parser);
	}
	catch (const ParserException& e)
	{
		Debug& debug = Debug::GetInstance();
		debug.Print(debug.GetDebugLevelName(DebugLevel::ERROR));
		debug.Print("Failed to serialize level \"" + levelName + "\": ");
		debug.PrintLn(e.what());
	}
}

void Junior::GameObjectFactory::FillLevel(const std::string& levelName, Level* level) const
{
	Parser parser(filePath_ + levelName + levelFileExtenion_, std::ios_base::in);
	// When we start reading objects, keep track of the current one we are reading so that we can release it in case things go wrong
	GameObject* current = nullptr;
	std::string name;
	try
	{
		// Skip the name of the file
		parser.Skip(levelName);
		// Skip the openning bracket
		parser.Skip("{");
		// Start reading archetypes
		unsigned numArchetypes;
		parser.ReadVariable("numArchetypes", numArchetypes);
		parser.Skip("{");
		for (unsigned i = 0; i < numArchetypes; ++i)
		{
			// Start reading archetypes
			parser.ReadValue(name);
			// Check if the first character of the name is a octothorp, if so then check the file with the same name
			if (name[0] == '#')
			{
				current = CreateObject(name.substr(1), true);
			}
			else
			{
				current = new GameObject(name, true);
				current->Deserialize(parser);
			}
			// Put the archetype into the object manager
			level->GetOwner()->GetObjectManager()->AddArchetype(current);
		}
		parser.Skip("}");

		// Start reading objects
		unsigned numObjects;
		parser.ReadVariable("numGameObjects", numObjects);
		parser.Skip("{");
		for (unsigned i = 0; i < numObjects; ++i)
		{
			// Start reading objects
			// Read the name of the game object
			parser.ReadValue(name);
			// If the name starts with a #, then we attempt to find an archetype with the same name without the octothorp
			if (name.at(0) == '#')
			{
				// Attempt to find an archetype
				current = level->GetOwner()->GetObjectManager()->CreateFromArchetype(name.substr(1));
			}
			else
			{
				current = new GameObject(name);
				current->Deserialize(parser);
			}
			// Put the game object into the manager
			level->GetOwner()->GetObjectManager()->AddObject(current);
		}
		parser.Skip("}");
	}
	catch (const ParserException& e)
	{
		// Delete the object that went wrong
		delete current;
		// Print out the debug error
		Debug& debug = Debug::GetInstance();
		debug.Print(debug.GetDebugLevelName(DebugLevel::ERROR));
		debug.Print("Failed to load level \"" + name + "\": ");
		debug.PrintLn(e.what());
	}
}



Junior::GameObjectFactory& Junior::GameObjectFactory::GetInstance()
{
	static GameObjectFactory instance;
	return instance;
}