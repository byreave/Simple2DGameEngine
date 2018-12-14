#include "MemorySystem.h"
#include "HeapManager.h"
#include "FixedSizeAllocator.h"


FSAInitData FSASizes[] = { {16, 100}, {32, 200}, {96, 400} };


bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	// create your HeapManager and FixedSizeAllocators
	HeapManager::pHeapManager = HeapManager::create(i_pHeapMemory, i_sizeHeapMemory, i_OptionalNumDescriptors);
	if (HeapManager::pHeapManager == nullptr)
		return false;
	for (unsigned int i = 0; i < numFSAs; ++i)
	{
		FSAs[i] = FixedSizeAllocator::CreateFixedSizeAllocator(FSASizes[i].sizeBlock, FSASizes[i].numBlocks, HeapManager::pHeapManager);
		if (FSAs[i] == nullptr)
			return false;
	}
	return true;
}

void Collect()
{
	HeapManager::pHeapManager->collect();
	// coalesce free blocks
	// you may or may not need to do this depending on how you've implemented your HeapManager
}

void DestroyMemorySystem()
{
	HeapManager::pHeapManager->destroy();
	// Destroy your HeapManager and FixedSizeAllocators
}

FixedSizeAllocator * FindFixedSizeAllocator(size_t i_size)
{
	for (unsigned int i = 0; i < numFSAs; ++i)
	{
		if (i_size < FSASizes[i].sizeBlock)
			return FSAs[i];
	}
	return nullptr;
}

