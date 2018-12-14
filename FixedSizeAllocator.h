#pragma once
#include "BitArray.h"
#include "HeapManager.h"
class FixedSizeAllocator
{
public:
	static FixedSizeAllocator* CreateFixedSizeAllocator(size_t i_sizeBlock, size_t i_numBlock, HeapManager * defaultHeap);
	~FixedSizeAllocator();

	void * _alloc(size_t i_size);
	bool _free(void * i_ptr);
	bool Contains(void * i_ptr) const;
private:
	size_t m_sizeBlock;
	size_t m_numBlock;
	void * m_baseAddr;
	BitArray * m_bitArray;
};

