/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: GameObjectFactory.cpp
* Description: Constructs game objects and components from files
* Created: 9 Apr 2019
* Last Modified: 2 Oct 2019
*/

// Includes
#include <vector>		// Vector
#include <string>		// String
#include "Parser.h"		// Parser

namespace Junior
{
	// Forward Declarations
	class ComponentContainer;
	class Level;
	class GameObject;

	class GameObjectFactory
	{
	private:
		// Private Member Variables

		// The vector containing all the prepared components for deserialization
		std::vector<ComponentContainer*> preparedComponents_;
		// The target file path
		std::string filePath_;
		// File extention for objects
		std::string objectFileExtension_;
		// File extensions for levels
		std::string levelFileExtenion_;

		// Private Member Functions

		// Hide the constructor
		GameObjectFactory();
	public:
		// Public Member Functions

		// Destructor
		~GameObjectFactory();
		// Registers a component to the factory
		template <class T>
		void RegisterComponent()
		{
			preparedComponents_.push_back(new T);
		}
		// Creates a new component based the parser
		// Params:
		//	name: The name of the component
		// Returns: The component we created
		ComponentContainer* CreateComponent(const std::string& name) const;
		// Creates a new object based on the parser
		// Params:
		//	name: The name of the object we want to create
		//	asArchetype: Create the object as archetype
		// Returns: The object created
		GameObject* CreateObject(const std::string& name, bool asArchetype = false) const;
		// Saves an object to a file
		// Params:
		//	archetype: The object we are saving
		void SaveObject(const GameObject* archetype) const;
		// Save a level to a file
		// Params:
		//	level: The level we are saving
		void SaveLevel(const Level* level) const;
		// Fill a level with game objects
		// Params:
		//	name: The name of the level we are filling
		//	level: The level we are filling
		void FillLevel(const std::string& name, Level* level) const;
		// Returns: The instance of the game object factory
		static GameObjectFactory& GetInstance();
	};
}