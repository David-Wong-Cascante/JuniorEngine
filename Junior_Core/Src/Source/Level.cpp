/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Level.cpp
* Description: Defines what a level is, with game objects and everything
* Created: 20 Dec 2018
* Last Modified: 2 Oct 2019
*/

// Includes
#include "Level.h"
#include "GameObjectManager.h"			// Game Object Manager
#include "GameObject.h"					// Game Object
#include "Space.h"						// Space

Junior::Level::Level(const char* name)
	: GameSystem(name), owner_(nullptr)
{

}

bool Junior::Level::Load() { return true; }
bool Junior::Level::Initialize() { return true; }
void Junior::Level::Update(double) {}
void Junior::Level::Render() {}
void Junior::Level::Shutdown() {}
void Junior::Level::Unload() {}

void Junior::Level::Serialize(Parser& parser) const
{
	// Star the serialize by writing the name of the level and making the scope
	parser.WriteValue(GetName());
	parser.StarScope();
	// Then write the number of game objects present in the scene
	const std::vector<GameObject*>& objects = owner_->GetObjectManager()->GetAllObjects();
	parser.WriteVariable("numGameObjects", objects.size());
	// Then serialize every object independently
	auto cend = objects.cend();
	for (auto cbegin = objects.cbegin(); cbegin < cend; ++cbegin)
	{
		(*cbegin)->Serialize(parser);
	}
	parser.EndScope();
}

void Junior::Level::Deserialize(Parser& parser)
{

}

void Junior::Level::SetOwner(Junior::Space* space)
{
	owner_ = space;
}

Junior::Space* Junior::Level::GetOwner()
{
	return owner_;
}