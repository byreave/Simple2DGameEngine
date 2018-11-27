#pragma once
#include "HeapManager.h"
#include "ConsoleLog.h"
void * operator new(size_t i_size)
{
	if (HeapManager::pHeapManager != nullptr)
	{
		DEBUG_PRINT("MSG", "OVERRIDEN NEW CALLED!\n");

		return HeapManager::pHeapManager->_alloc(i_size);
	}
	return nullptr;
}

void operator delete(void * ptr)
{
	if (HeapManager::pHeapManager != nullptr)
	{
		DEBUG_PRINT("MSG", "OVERRIDEN DELETE CALLED!\n");
		HeapManager::pHeapManager->_free(ptr);
	}
}
//alignment
void * operator new(size_t i_size, size_t alignment, HeapManager * pHeapManager)
{
	if (HeapManager::pHeapManager != nullptr)
	{
		DEBUG_PRINT("MSG", "OVERRIDEN NEW CALLED!\n");

		return HeapManager::pHeapManager->_alloc(i_size, alignment);
	}
	return nullptr;
}

void operator delete(void * ptr, size_t alignment, HeapManager * pHeapManager)
{
	if (HeapManager::pHeapManager != nullptr)
	{
		DEBUG_PRINT("MSG", "OVERRIDEN DELETE CALLED!\n");
		HeapManager::pHeapManager->_free(ptr);
	}
}
void * operator new[](size_t i_size)
{
	if (HeapManager::pHeapManager != nullptr)
	{
		return HeapManager::pHeapManager->_alloc(i_size);
	}
	return nullptr;
}
void operator delete[](void * ptr)
{
	if (HeapManager::pHeapManager != nullptr)
	{
		HeapManager::pHeapManager->_free(ptr);
	}
}
