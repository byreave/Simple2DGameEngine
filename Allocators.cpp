#include <inttypes.h>
#include <malloc.h>
#include <assert.h>
#include "MemorySystem.h"
#include "HeapManager.h"
#include "FixedSizeAllocator.h"
#include <stdio.h>

FixedSizeAllocator * FSAs[numFSAs] = {};
void * __cdecl malloc(size_t i_size)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	FixedSizeAllocator * FSA = FindFixedSizeAllocator(i_size);
	if (FSA != nullptr)
	{
		printf("malloc %zu on FSAs.\n", i_size);
		return FSA->_alloc(i_size);
	}
	else
	{
		printf("malloc %zu on the default heap.\n", i_size);
		return HeapManager::pHeapManager->_alloc(i_size);
	}
}

void __cdecl free(void * i_ptr)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	if (HeapManager::pHeapManager->Contains(i_ptr))
	{
		printf("free 0x%" PRIXPTR " on the default heap.\n", reinterpret_cast<uintptr_t>(i_ptr));
		HeapManager::pHeapManager->_free(i_ptr);
	}
	else
	{
		for (unsigned int i = 0; i < numFSAs; ++i)
		{
			assert(FSAs[i]);
			if (FSAs[i]->Contains(i_ptr))
			{
				printf("free 0x%" PRIXPTR " on the number %d FSA.\n", reinterpret_cast<uintptr_t>(i_ptr), i);
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
	if (FSA != nullptr)
	{
		printf("new %zu on FSAs.\n", i_size);
		return FSA->_alloc(i_size);
	}
	else
	{
		printf("new %zu on the default heap.\n", i_size);
		return HeapManager::pHeapManager->_alloc(i_size);
	}
}

void operator delete(void * i_ptr)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	if (HeapManager::pHeapManager->Contains(i_ptr))
	{
		printf("delete 0x%" PRIXPTR " on the default heap.\n", reinterpret_cast<uintptr_t>(i_ptr));
		HeapManager::pHeapManager->_free(i_ptr);
	}
	else
	{
		for (unsigned int i = 0; i < numFSAs; ++i)
		{
			assert(FSAs[i]);
			if (FSAs[i]->Contains(i_ptr))
			{
				printf("delete 0x%" PRIXPTR " on the number %d FSA.\n", reinterpret_cast<uintptr_t>(i_ptr), i);
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
	if (FSA != nullptr)
	{
		printf("new [] %zu on FSAs.\n", i_size);
		return FSA->_alloc(i_size);
	}
	else
	{
		printf("new [] %zu on the default heap.\n", i_size);
		return HeapManager::pHeapManager->_alloc(i_size);
	}
}

void operator delete [](void * i_ptr)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	if (HeapManager::pHeapManager->Contains(i_ptr))
	{
		printf("delete [] 0x%" PRIXPTR " on the default heap.\n", reinterpret_cast<uintptr_t>(i_ptr));
		HeapManager::pHeapManager->_free(i_ptr);
	}
	else
	{
		for (unsigned int i = 0; i < numFSAs; ++i)
		{
			assert(FSAs[i]);
			if (FSAs[i]->Contains(i_ptr))
			{
				printf("delete [] 0x%" PRIXPTR " on the number %d FSA.\n", reinterpret_cast<uintptr_t>(i_ptr), i);
				FSAs[i]->_free(i_ptr);
				break;
			}
		}
	}
}