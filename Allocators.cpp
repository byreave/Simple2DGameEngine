#include <inttypes.h>
#include <malloc.h>
#include <assert.h>
#include "MemorySystem.h"
#include "HeapManager.h"
#include "FixedSizeAllocator.h"
#include <stdio.h>


void * __cdecl malloc(size_t i_size)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	FixedSizeAllocator * FSA = FindFixedSizeAllocator(i_size);
	printf("malloc %zu\n", i_size);
	if (FSA != nullptr)
		return FSA->_alloc(i_size);
	else
		return HeapManager::pHeapManager->_alloc(i_size);
}

void __cdecl free(void * i_ptr)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("free 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
	if (HeapManager::pHeapManager->Contains(i_ptr))
		HeapManager::pHeapManager->_free(i_ptr);
	else
	{
		for (unsigned int i = 0; i < numFSAs; ++i)
		{
			assert(FSAs[i]);
			if (FSAs[i]->Contains(i_ptr))
			{
				FSAs[i]->_free(i_ptr);
				break;
			}
		}
	}
}

void * operator new(size_t i_size)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	FixedSizeAllocator * FSA = FindFixedSizeAllocator(i_size);
	printf("new %zu\n", i_size);
	if (FSA != nullptr)
		return FSA->_alloc(i_size);
	else
		return HeapManager::pHeapManager->_alloc(i_size);
}

void operator delete(void * i_ptr)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("delete 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
	if (HeapManager::pHeapManager->Contains(i_ptr))
		HeapManager::pHeapManager->_free(i_ptr);
	else
	{
		for (unsigned int i = 0; i < numFSAs; ++i)
		{
			assert(FSAs[i] != nullptr);
			if (FSAs[i]->Contains(i_ptr))
			{
				FSAs[i]->_free(i_ptr);
				break;
			}
		}
	}
}

void * operator new[](size_t i_size)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	FixedSizeAllocator * FSA = FindFixedSizeAllocator(i_size);
	printf("new [] %zu\n", i_size);
	if (FSA != nullptr)
		return FSA->_alloc(i_size);
	else
		return HeapManager::pHeapManager->_alloc(i_size);
}

void operator delete [](void * i_ptr)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("delete [] 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
	if (HeapManager::pHeapManager->Contains(i_ptr))
		HeapManager::pHeapManager->_free(i_ptr);
	else
	{
		for (unsigned int i = 0; i < numFSAs; ++i)
		{
			assert(FSAs[i]);
			if (FSAs[i]->Contains(i_ptr))
			{
				FSAs[i]->_free(i_ptr);
				break;
			}
		}
	}
}