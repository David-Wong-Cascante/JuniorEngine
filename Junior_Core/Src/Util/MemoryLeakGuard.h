#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: MemoryLeakGuard.h
* Description: Gives warnings about memory leaks
* Created: 19-Jan-2019
* Last Modified: 19-Jan-2019
*/

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
	// Create the new keyword to create debug allocations
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif