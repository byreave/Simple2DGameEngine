#include "FixedSizeAllocator.h"
#include <string.h>
#ifdef _DEBUG
static unsigned char _bNoMansLandFill = 0xFD; /* fill no-man's land with this */
#define nNoMansLandSize 4
#endif // _DEBUG
static unsigned char _bAlignLandFill = 0xED; /* fill no-man's land for aligned routines */
static unsigned char _bDeadLandFill = 0xDD; /* fill free objects with this */
static unsigned char _bCleanLandFill = 0xCD; /* fill new objects with this */

FixedSizeAllocator * FixedSizeAllocator::CreateFixedSizeAllocator(size_t i_sizeBlock, size_t i_numBlock, HeapManager * defaultHeap)
{
	FixedSizeAllocator * newFSA = static_cast<FixedSizeAllocator *>(defaultHeap->_alloc(sizeof(FixedSizeAllocator)));
	newFSA->m_sizeBlock = i_sizeBlock;
	newFSA->m_numBlock = i_numBlock;
	newFSA->m_baseAddr = defaultHeap->_alloc(i_sizeBlock * i_numBlock);
	return newFSA;
}

FixedSizeAllocator::~FixedSizeAllocator()
{
}
