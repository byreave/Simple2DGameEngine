#include "FixedSizeAllocator.h"
#include "ConsoleLog.h"
#include <string.h>
#include <assert.h>
#include <inttypes.h>
#ifdef _DEBUG
static unsigned char _bNoMansLandFill = 0xFD; /* fill no-man's land with this */
static unsigned char _bAlignLandFill = 0xED; /* fill no-man's land for aligned routines */
static unsigned char _bDeadLandFill = 0xDD; /* fill free objects with this */
static unsigned char _bCleanLandFill = 0xCD; /* fill new objects with this */
#define nNoMansLandSize 4
#endif // _DEBUG

FixedSizeAllocator * FixedSizeAllocator::CreateFixedSizeAllocator(size_t i_sizeBlock, size_t i_numBlock, HeapManager * defaultHeap)
{
	FixedSizeAllocator * newFSA = static_cast<FixedSizeAllocator *>(defaultHeap->_alloc(sizeof(FixedSizeAllocator)));
	if (newFSA == nullptr)
		return nullptr;
	newFSA->m_sizeBlock = i_sizeBlock;
	newFSA->m_numBlock = i_numBlock;
#ifdef _DEBUG
	//two adjacent blocks can share a guardband block, thus there are i_numBlock + 1 guardbanding blocks
	newFSA->m_baseAddr = defaultHeap->_alloc(i_sizeBlock * i_numBlock + nNoMansLandSize * (i_numBlock + 1));
	unsigned char * tmpGuardband = static_cast<unsigned char *>(newFSA->m_baseAddr);
	for (unsigned int i = 0; i < i_numBlock; ++i)
	{
		memset(tmpGuardband, _bNoMansLandFill, nNoMansLandSize);
		tmpGuardband += nNoMansLandSize + i_sizeBlock;
	}
#else
	newFSA->m_baseAddr = defaultHeap->_alloc(i_sizeBlock * i_numBlock);
#endif // _DEBUG
	if (newFSA->m_baseAddr == nullptr)
	{
		defaultHeap->_free(newFSA);
		newFSA = nullptr;
		return nullptr;
	}
	newFSA->m_bitArray = BitArray::CreateBitArray(i_numBlock, false, defaultHeap);
	if (newFSA->m_bitArray == nullptr)
	{
		defaultHeap->_free(newFSA->m_baseAddr);
		newFSA->m_baseAddr = nullptr;
		defaultHeap->_free(newFSA);
		newFSA = nullptr;
		return nullptr;
	}
	return newFSA;
}

FixedSizeAllocator::~FixedSizeAllocator()
{
#ifdef _DEBUG
	unsigned long clearBit;
	if (!m_bitArray->GetFirstClearBit(clearBit))
	{
		DEBUG_PRINT("Warning", "Outstanding blocks index %d found in this heap while destructing.\n", clearBit);
	}
	memset(m_baseAddr, _bDeadLandFill, m_sizeBlock * m_numBlock + nNoMansLandSize * (m_numBlock + 1));
#endif // _DEBUG
	if(m_bitArray != nullptr)
		delete m_bitArray;
	m_bitArray = nullptr;
	if(m_baseAddr != nullptr)
		delete m_baseAddr;
	m_baseAddr = nullptr;
}

void * FixedSizeAllocator::_alloc(size_t i_size)
{
	assert(i_size <= m_sizeBlock);
	unsigned long availableBlock;
	if (!m_bitArray->GetFirstSetBit(availableBlock))
		return nullptr;
	m_bitArray->ClearBit(availableBlock);
#ifdef _DEBUG
	//fill value
	return memset(static_cast<unsigned char *>(m_baseAddr) + nNoMansLandSize + (m_sizeBlock + nNoMansLandSize) * availableBlock, _bCleanLandFill, i_size);
#else
	return static_cast<unsigned char *>(m_baseAddr) + m_sizeBlock * availableBlock;
#endif // _DEBUG
}

bool FixedSizeAllocator::_free(void * i_ptr)
{
	//if
	//1. i_ptr is within the range of the heap
	//2. i_ptr is at the right position
	//3. the block is outstanding
#ifdef _DEBUG
	size_t bitIndex = (static_cast<unsigned char *>(i_ptr) - nNoMansLandSize - static_cast<unsigned char *>(m_baseAddr)) / (m_sizeBlock + nNoMansLandSize);
	if (i_ptr >= m_baseAddr &&
		i_ptr <= static_cast<unsigned char *>(m_baseAddr) + m_sizeBlock * m_numBlock + nNoMansLandSize * (m_numBlock + 1) //&&
		//(static_cast<unsigned char *>(i_ptr) - nNoMansLandSize - static_cast<unsigned char *>(m_baseAddr)) % (m_sizeBlock + nNoMansLandSize) == 0 &&
		//m_bitArray->IsBitClear(bitIndex)
		)
	{
		if (m_bitArray->IsBitClear(bitIndex))
		{
			m_bitArray->SetBit(bitIndex);
			return true;
		}
		else
		{
			DEBUG_PRINT("Error", "Address 0x%" PRIXPTR " is not clear.\n", reinterpret_cast<uintptr_t>(i_ptr));
			return false;
		}
	}
	else
	{
		DEBUG_PRINT("Error", "Address 0x%" PRIXPTR " is not in the FSA.\n", reinterpret_cast<uintptr_t>(i_ptr));
		return false;
	}
#else
	size_t bitIndex = (static_cast<unsigned char *>(i_ptr)  - static_cast<unsigned char *>(m_baseAddr)) / m_sizeBlock;
	if (i_ptr >= m_baseAddr &&
		(i_ptr <= static_cast<unsigned char *>(m_baseAddr) + m_sizeBlock * m_numBlock) &&
		(static_cast<unsigned char *>(i_ptr) - static_cast<unsigned char *>(m_baseAddr)) % m_sizeBlock == 0 &&
		m_bitArray->IsBitClear(bitIndex)
		)
	{
		m_bitArray->SetBit(bitIndex);
		return true;
	}
	else
		return false;
#endif // _DEBUG

}

bool FixedSizeAllocator::Contains(void * i_ptr) const
{
#ifdef _DEBUG
	if (i_ptr >= m_baseAddr && i_ptr < static_cast<unsigned char *>(m_baseAddr) + m_sizeBlock * m_numBlock + nNoMansLandSize * (m_numBlock + 1))
#else
	if (i_ptr >= m_baseAddr && i_ptr < static_cast<unsigned char *>(m_baseAddr) + m_sizeBlock * m_numBlock)
#endif // _DEBUG
		return true;
	return false;
}
