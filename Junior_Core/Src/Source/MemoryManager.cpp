#pragma once
/* 
 * Author: David Wong, with the help of Nathan Mueller (nathan.mueller@digipen.edu)
 * Email: david.wongcascante@digipen.edu
 * Date Created: 3-Jun-2018
 * Last Modified: 29-Oct-2018
 * File Name: MemoryManager.cpp
 * Description: Define the Memory Manager
*/

// Includes //
#include "MemoryManager.h"

#include <stdio.h>

// Public Member Function //
Junior::MemoryManager::MemoryManager() 
	: memory_(0), freeList_(0)
{
}

void* Junior::MemoryManager::Allocate(unsigned int size)
{
	// Malloc new blocks if we are out of them
	if (freeList_ == 0)
	{
		freeList_ = MakeNewPage();
		memory_ = reinterpret_cast<unsigned char**>(freeList_);
	}

	// Check that the amount of memory actually fits into the block size
	if (size <= PAYLOAD_SIZE)
	{
		Block* blockToGive = freeList_;
		freeList_ = freeList_->nextBlock_;
		blockToGive->nextBlock_ = 0;
		blockToGive->blockHeader_.inUse_ = true;
		return (reinterpret_cast<char*>(blockToGive) + sizeof(BlockHeader));
	}

	return 0;
}

void Junior::MemoryManager::DeAllocate(void* block)
{
	unsigned char* page = 0;
	// Mark the block as in not in use
	page = reinterpret_cast<unsigned char*>(block) - sizeof(BlockHeader);
	Block* returnedBlock = reinterpret_cast<Block*>(page);
	returnedBlock->blockHeader_.inUse_ = false;
	// Find the start of the page that block came from
	while (!reinterpret_cast<Block*>(page)->blockHeader_.firstInPage_)
	{
		page -= sizeof(BlockHeader) + PAYLOAD_SIZE;
	}

	// If every block on the page is not in use
	Block* iterator = 0;
	for (int i = 0; i < BLOCKS_PER_PAGE; ++i)
	{
		iterator = reinterpret_cast<Block*>(page + (i * (sizeof(BlockHeader) + PAYLOAD_SIZE)));
		// If we find a block in the page that is still in use, we cannot delete the whole page and as a result
		// we just stick this piece of memory into the free list
		if (iterator->blockHeader_.inUse_)
		{
			iterator->nextBlock_ = freeList_;
			freeList_ = iterator;
			return;
		}
	}

	// Remove all blocks in the page from the free list
	// See if the head is on the page, if so then remove it and repeat the process until the head of the list is not within the page
	while (reinterpret_cast<unsigned char*>(freeList_) >= page && reinterpret_cast<unsigned char*>(freeList_) < page + (BLOCKS_PER_PAGE * (sizeof(BlockHeader) + PAYLOAD_SIZE)))
	{
		// If we find that the tail of the list is the same as the head, then
		// we have to quit out of the loop because otherwise it goes forever
		if (freeList_ == freeList_->nextBlock_)
		{
			break;
		}

		freeList_ = freeList_->nextBlock_;
	}

	Block* prevBlock = freeList_;
	if (prevBlock)
	{
		iterator = prevBlock->nextBlock_;
	}

	while(iterator)
	{
		// If the iterator is within the page then remove it from the linked list
		if (page >= reinterpret_cast<unsigned char*>(iterator) && reinterpret_cast<unsigned char*>(iterator) < (page + (sizeof(BlockHeader) + PAYLOAD_SIZE) * BLOCKS_PER_PAGE) &&
			prevBlock)
		{
			prevBlock->nextBlock_ = iterator->nextBlock_;
			iterator->nextBlock_ = 0;
		}

		// Move along the free list
		prevBlock = iterator;
		iterator = iterator->nextBlock_;
	}
	
	// Finally, free the page
	//free(page);
	delete[] page;
}

// Private Member Functions //
// Helper Functoins
Junior::Block* Junior::MemoryManager::MakeNewPage()
{
	// Make the list's head
	Block* newFreeBlocks = 0;
	// Allocate enough memory to allocate n block pointers with the max block size and the header
	//char* rawMemory = reinterpret_cast<char*>(malloc((PAYLOAD_SIZE + sizeof(BlockHeader)) * BLOCKS_PER_PAGE));
	char* rawMemory = new char[(PAYLOAD_SIZE + sizeof(BlockHeader)) * BLOCKS_PER_PAGE];
	// For debug purposes, set all bytes in the memory to 0xFF
	for (int i = 0; i < BLOCKS_PER_PAGE * (PAYLOAD_SIZE + sizeof(BlockHeader)); ++i)
	{
		rawMemory[i] = (char)0xFF;
	}
	// Split the raw memory into blocks that are in a linked list
	char* nextBlockAddress = 0;
	newFreeBlocks = reinterpret_cast<Block*>(rawMemory);
	for(int i = 0; i < BLOCKS_PER_PAGE; ++i)
	{
		// Make sure we set the first block in the page as the first
		newFreeBlocks->blockHeader_.firstInPage_ = i == 0;
		// We are not using the block for right now
		newFreeBlocks->blockHeader_.inUse_ = false;

		// Correctly set the pointer to the next block
		if (i == (BLOCKS_PER_PAGE - 1))
		{
			newFreeBlocks->nextBlock_ = 0;
		}
		else
		{
			// Get the next element in the free list
			nextBlockAddress = reinterpret_cast<char*>(newFreeBlocks);
			nextBlockAddress += sizeof(BlockHeader) + PAYLOAD_SIZE;
			// Update the free list and add the next free block in memory
			newFreeBlocks->nextBlock_ = reinterpret_cast<Block*>(nextBlockAddress);
			// Iterate through the free list
			newFreeBlocks = newFreeBlocks->nextBlock_;
		}
	}
	return reinterpret_cast<Block*>(rawMemory);
}