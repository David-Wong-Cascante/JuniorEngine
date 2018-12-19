#pragma once
/* 
 * Author: David Wong, with the help of Nathan Mueller (nathan.mueller@digipen.edu)
 * Email: david.wongcascante@digipen.edu
 * Date Created: 3-Jun-2018
 * Last Modified: 29-Oct-2018
 * File Name: MemoryManager.h
 * Description: Declare the Memory Manager that the Junior Engine will use to grab memory efficienly
	* Maybe we should also override every object to use this so that we can just call 'new' in each new pointer
	* and have it use the Memory Manager
*/

// Defines //
#define PAYLOAD_SIZE 512
#define BLOCKS_PER_PAGE 16

namespace Junior
{
	/* Struct Size: 4*/
	struct BlockHeader
	{
		// Public Struct Variables //
		// The first physical page in memory
		int firstInPage_;
		// If the page is using
		int inUse_;
	};
	/*
	 * Header: Size 4 | [Including Next Block] Memory Block: Size - sizeof(Header) Bytes | 
	 */
	struct Block
	{
		// Public Sturct Variables //
		/* Header */
		BlockHeader blockHeader_;
		/* Payload */
		Block* nextBlock_;
	};

	class MemoryManager
	{
	private:
		// Private Class Variables // 
		// The raw memory of the manager
		unsigned char** memory_;
		// The whole free list
		Block* freeList_;

		// Private Member Functions //
		// Creates a new page
		// Returns: A new memory page
		Block* MakeNewPage();
		// Hiding Constructor
		// Params:
		//	other: Another memory manager
		MemoryManager(MemoryManager &other);
	public:
		// Public Member Functions //
		// Constructor
		MemoryManager();
		// Allocates the memory to save objects in
		// Params:
		//	size: The size of the object
		// Returns: A pointer to empty piece of memory
		void* Allocate(unsigned int size);
		// Deallocates the memory that the object is saved in
		// Params:
		//	memory: A pointer to the memory to be freed by the memory manager
		void DeAllocate(void* memory);
	};
}