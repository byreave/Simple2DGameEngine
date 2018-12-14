#pragma once
class FixedSizeAllocator;

struct FSAInitData
{
	size_t	sizeBlock;
	size_t	numBlocks;
};

FSAInitData FSASizes[];
const static size_t numFSAs = 3;
extern FixedSizeAllocator * FSAs[numFSAs];

// InitializeMemorySystem - initialize your memory system including your HeapManager and some FixedSizeAllocators
bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors);

// Collect - coalesce free blocks in attempt to create larger blocks
void Collect();

// DestroyMemorySystem - destroy your memory systems
void DestroyMemorySystem();

//Find the right size FSA
FixedSizeAllocator * FindFixedSizeAllocator(size_t i_size);