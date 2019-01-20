/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Level.cpp
* Description: Defines what a level is, with game objects and everything
* Created: 20-Dec-2018
* Last Modified: 20-Dec-2018
*/

// Includes
#include "Level.h"

Junior::Level::Level(const char* name)
	: GameSystem(name)
{

}

bool Junior::Level::Load() { return true; }
bool Junior::Level::Initialize() { return true; }
void Junior::Level::Update(double) {}
void Junior::Level::Render() {}
void Junior::Level::Shutdown() {}
void Junior::Level::Unload() {}