#pragma once
#include "BitArray.h"
class FixedSizeAllocator
{
public:
	FixedSizeAllocator();
	~FixedSizeAllocator();
private:
	size_t m_sizeBlock;
	size_t m_numBlock;
	void * m_baseAddr;
	BitArray * m_bitArray;
};

