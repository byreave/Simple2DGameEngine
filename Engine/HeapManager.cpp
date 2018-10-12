#include "HeapManager.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#ifdef _DEBUG
static unsigned char _bNoMansLandFill = 0xFD; /* fill no-man's land with this */
#define nNoMansLandSize 4
#endif // _DEBUG
static unsigned char _bAlignLandFill = 0xED; /* fill no-man's land for aligned routines */
static unsigned char _bDeadLandFill = 0xDD; /* fill free objects with this */
static unsigned char _bCleanLandFill = 0xCD; /* fill new objects with this */


HeapManager * HeapManager::create(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
{
	void * endOfHeap = (unsigned char *)i_pMemory + i_sizeMemory;
	void * startOfDescriptors = (unsigned char *)endOfHeap - i_numDescriptors * sizeof(BlockDescriptor);
	//Put heapmanager before descriptors
	HeapManager * heapManager = (HeapManager *)((unsigned char *)startOfDescriptors - sizeof(HeapManager));
	heapManager->pHeapMemory = i_pMemory;
	heapManager->numDescritors = i_numDescriptors;
	heapManager->sizeHeap = i_sizeMemory;
	//intialize all free block descriptors in successive order
	heapManager->m_FreeBlockListHead = (BlockDescriptor *)startOfDescriptors;
	heapManager->m_FreeBlockListHead->m_pBlockStartAddr = i_pMemory;
	heapManager->m_FreeBlockListHead->m_sizeBlock = i_sizeMemory - i_numDescriptors * sizeof(BlockDescriptor) - sizeof(HeapManager);
	heapManager->m_OutstandingBlockListHead = nullptr;
	BlockDescriptor * tmp = heapManager->m_FreeBlockListHead;
	for (int i = 0; i < i_numDescriptors-1; i++)
	{
		tmp->next = tmp + 1;
		tmp = tmp->next;
		tmp->m_sizeBlock = 0;
		tmp->m_pBlockStartAddr = nullptr;
	}
	//last descriptor
	tmp->next = nullptr;
	return heapManager;
}

void HeapManager::destroy()
{
	memset(pHeapMemory, 0x00, sizeHeap);
}

void * HeapManager::_alloc(size_t i_size)
{
	//if (m_FreeBlockListHead == nullptr)
	//	return nullptr;
	BlockDescriptor * curFreeBlock = m_FreeBlockListHead;
	BlockDescriptor * prevFreeBlock = nullptr;
#ifdef _DEBUG
	while (curFreeBlock->m_sizeBlock < i_size + nNoMansLandSize * 2 && curFreeBlock != nullptr)
#else
	while (curFreeBlock->m_sizeBlock < i_size && curFreeBlock != nullptr)
#endif // _DEBUG
	{
		prevFreeBlock = curFreeBlock;
		curFreeBlock = curFreeBlock->next;
	}

	if (curFreeBlock == nullptr)
		return nullptr;
	//exactly the size
#ifdef _DEBUG
	if (curFreeBlock->m_sizeBlock  == i_size + nNoMansLandSize * 2)
#else
	if (curFreeBlock->m_sizeBlock == i_size)
#endif // _DEBUG
	{
		//when it is the free block list head
		if (prevFreeBlock == nullptr)
		{
			m_FreeBlockListHead = nullptr;
		}
		else
		{
			prevFreeBlock->next = curFreeBlock->next;
		}
	}
	else
	{
		BlockDescriptor * m_FreeBlockListTail = m_FreeBlockListHead, *m_PrevFreeBlockListTail = nullptr;
		//get last node of free block list
		while (m_FreeBlockListTail->m_pBlockStartAddr != nullptr && m_FreeBlockListTail != nullptr)
		{
			m_PrevFreeBlockListTail = m_FreeBlockListTail;
			m_FreeBlockListTail = m_FreeBlockListTail->next;
		}
		//this is not supposed to happen but.
		if (m_PrevFreeBlockListTail == nullptr)
		{
			//can add console log here
			return false;
		}
		//not enough block descriptor
		if (m_FreeBlockListTail == nullptr)
		{
			m_FreeBlockListHead = nullptr;
		}
		//when it is the free block list head
		if (prevFreeBlock == nullptr)
		{
			m_FreeBlockListHead = m_FreeBlockListTail;
			m_FreeBlockListTail = m_FreeBlockListTail->next;
			m_PrevFreeBlockListTail->next = m_FreeBlockListTail;
#ifdef _DEBUG
			m_FreeBlockListHead->m_sizeBlock = curFreeBlock->m_sizeBlock - i_size - nNoMansLandSize * 2;
			m_FreeBlockListHead->m_pBlockStartAddr = (unsigned char *)curFreeBlock->m_pBlockStartAddr + i_size + nNoMansLandSize * 2;
#else
			m_FreeBlockListHead->m_sizeBlock = curFreeBlock->m_sizeBlock - i_size;
			m_FreeBlockListHead->m_pBlockStartAddr = (unsigned char *)curFreeBlock->m_pBlockStartAddr + i_size;
#endif // _DEBUG

			if (m_FreeBlockListHead->next == curFreeBlock->next) //Tail is the next of head
				m_FreeBlockListHead->next = m_FreeBlockListTail;
			else
				m_FreeBlockListHead->next = curFreeBlock->next;

		}
		else
		{
			prevFreeBlock->next = m_FreeBlockListTail;
			m_FreeBlockListTail = m_FreeBlockListTail->next;
			m_PrevFreeBlockListTail->next = m_FreeBlockListTail;
#ifdef _DEBUG
			prevFreeBlock->next->m_sizeBlock = curFreeBlock->m_sizeBlock - i_size - nNoMansLandSize * 2;
			m_FreeBlockListHead->m_pBlockStartAddr = (unsigned char *)curFreeBlock->m_pBlockStartAddr + i_size + nNoMansLandSize * 2;
#else
			prevFreeBlock->next->m_sizeBlock = curFreeBlock->m_sizeBlock - i_size;
			m_FreeBlockListHead->m_pBlockStartAddr = (unsigned char *)curFreeBlock->m_pBlockStartAddr + i_size;
#endif // _DEBUG
			prevFreeBlock->next->next = curFreeBlock->next;
		}
	}
	curFreeBlock->next = m_OutstandingBlockListHead;
	curFreeBlock->m_sizeBlock = i_size;
#ifdef _DEBUG
	//guardbanding
	memset(curFreeBlock->m_pBlockStartAddr, _bNoMansLandFill, nNoMansLandSize);
	curFreeBlock->m_pBlockStartAddr = (unsigned char *)curFreeBlock->m_pBlockStartAddr + nNoMansLandSize;
	memset((unsigned char *)curFreeBlock->m_pBlockStartAddr + curFreeBlock->m_sizeBlock, _bNoMansLandFill, nNoMansLandSize);
#endif // _DEBUG
	//fillvalues
	memset(curFreeBlock->m_pBlockStartAddr, _bCleanLandFill, curFreeBlock->m_sizeBlock);
	m_OutstandingBlockListHead = curFreeBlock;
	return curFreeBlock->m_pBlockStartAddr;
}

void * HeapManager::_alloc(size_t i_size, size_t i_alignment)
{
	//(reinterpret_cast<uintptr_t>(pPtr) & (alignment - 1)) == 0
	if (i_alignment % 4 != 0)
		return nullptr;
	BlockDescriptor * curFreeBlock = m_FreeBlockListHead;
	BlockDescriptor * prevFreeBlock = nullptr;
	size_t alignOffset = 0;
	void * alignAddr = nullptr;
	while (curFreeBlock != nullptr)
	{
#ifdef _DEBUG
		//if the block size is less than required size continue (for a little efficiency)
		if (curFreeBlock->m_sizeBlock < i_size + nNoMansLandSize * 2)
		{
			prevFreeBlock = curFreeBlock;
			curFreeBlock = curFreeBlock->next;
			alignOffset = 0;
			continue;
		}
		alignAddr = (unsigned char *)curFreeBlock->m_pBlockStartAddr + nNoMansLandSize;
#else
		alignAddr = curFreeBlock->m_pBlockStartAddr;
#endif // _DEBUG

		while ((reinterpret_cast<uintptr_t>(alignAddr) & (i_alignment - 1)) != 0)
		{
			alignAddr = (unsigned char *)alignAddr + 1;
			alignOffset++;
		}
#ifdef _DEBUG
		if (curFreeBlock->m_sizeBlock >= i_size + nNoMansLandSize * 2 + alignOffset)
#else
		if (curFreeBlock->m_sizeBlock >= i_size + alignOffset)
#endif // _DEBUG
			break;
		prevFreeBlock = curFreeBlock;
		curFreeBlock = curFreeBlock->next;
		alignOffset = 0;
	}
	if (curFreeBlock == nullptr)
		return nullptr;
#ifdef _DEBUG
	if (curFreeBlock->m_sizeBlock  == i_size + alignOffset + nNoMansLandSize * 2)
#else
	if (curFreeBlock->m_sizeBlock  == i_size + alignOffset)
#endif // _DEBUG
	{
		//when it is the free block list head
		if (prevFreeBlock == nullptr)
		{
			m_FreeBlockListHead = nullptr;
		}
		else
		{
			prevFreeBlock->next = curFreeBlock->next;
		}
	}
	else
	{
		BlockDescriptor * m_FreeBlockListTail = m_FreeBlockListHead, *m_PrevFreeBlockListTail = nullptr;
		//get last node of free block list
		while (m_FreeBlockListTail != nullptr && m_FreeBlockListTail->m_pBlockStartAddr != nullptr)
		{
			m_PrevFreeBlockListTail = m_FreeBlockListTail;
			m_FreeBlockListTail = m_FreeBlockListTail->next;
		}
		//this is not supposed to happen but.
		if (m_PrevFreeBlockListTail == nullptr)
		{
			//can add console log here
			return nullptr;
		}
		//not enough descriptors
		if (m_FreeBlockListTail == nullptr)
			return nullptr;
		//when it is the free block list head
		if (prevFreeBlock == nullptr)
		{
			m_FreeBlockListHead = m_FreeBlockListTail;
			m_FreeBlockListTail = m_FreeBlockListTail->next;
			m_PrevFreeBlockListTail->next = m_FreeBlockListTail;
#ifdef _DEBUG
			m_FreeBlockListHead->m_sizeBlock = curFreeBlock->m_sizeBlock - i_size - nNoMansLandSize * 2 - alignOffset;
			m_FreeBlockListHead->m_pBlockStartAddr = (unsigned char *)curFreeBlock->m_pBlockStartAddr + alignOffset + i_size + nNoMansLandSize * 2;
#else
			m_FreeBlockListHead->m_sizeBlock = curFreeBlock->m_sizeBlock - i_size - alignOffset;
			m_FreeBlockListHead->m_pBlockStartAddr = (unsigned char *)curFreeBlock->m_pBlockStartAddr + alignOffset + i_size;
#endif // _DEBUG

			if (m_FreeBlockListHead->next == curFreeBlock->next) //Tail is the next of head
				m_FreeBlockListHead->next = m_FreeBlockListTail;
			else
				m_FreeBlockListHead->next = curFreeBlock->next;

		}
		else
		{
			prevFreeBlock->next = m_FreeBlockListTail;
			m_FreeBlockListTail = m_FreeBlockListTail->next;
			m_PrevFreeBlockListTail->next = m_FreeBlockListTail;
#ifdef _DEBUG
			prevFreeBlock->next->m_sizeBlock = curFreeBlock->m_sizeBlock - i_size - nNoMansLandSize * 2 - alignOffset;
			prevFreeBlock->next->m_pBlockStartAddr = (unsigned char *)curFreeBlock->m_pBlockStartAddr + alignOffset + i_size + nNoMansLandSize * 2;
#else
			prevFreeBlock->next->m_sizeBlock = curFreeBlock->m_sizeBlock - i_size - alignOffset;
			prevFreeBlock->next->m_pBlockStartAddr = (unsigned char *)curFreeBlock->m_pBlockStartAddr + alignOffset + i_size;
#endif // _DEBUG
			prevFreeBlock->next->next = curFreeBlock->next;
		}
	}
	curFreeBlock->next = m_OutstandingBlockListHead;
	//Fill values alignment
	memset(curFreeBlock->m_pBlockStartAddr, _bAlignLandFill, alignOffset);
	//move start addr
#ifdef _DEBUG
	curFreeBlock->m_pBlockStartAddr = (unsigned char *)alignAddr - nNoMansLandSize;
#else
	curFreeBlock->m_pBlockStartAddr = (unsigned char *)alignAddr;
#endif
	curFreeBlock->m_sizeBlock = i_size;
#ifdef _DEBUG
	//guardbanding
	memset(curFreeBlock->m_pBlockStartAddr, _bNoMansLandFill, nNoMansLandSize);
	curFreeBlock->m_pBlockStartAddr = (unsigned char *)curFreeBlock->m_pBlockStartAddr + nNoMansLandSize;
	memset((unsigned char *)curFreeBlock->m_pBlockStartAddr + curFreeBlock->m_sizeBlock, _bNoMansLandFill, nNoMansLandSize);
#endif // _DEBUG
	//fillvalues
	memset(curFreeBlock->m_pBlockStartAddr, _bCleanLandFill, curFreeBlock->m_sizeBlock);
	m_OutstandingBlockListHead = curFreeBlock;
	return curFreeBlock->m_pBlockStartAddr;
}

bool HeapManager::_free(void * i_ptr)
{
	BlockDescriptor * curOutstandingDesc = m_OutstandingBlockListHead, * prevOutstandingDesc = nullptr;
	while (curOutstandingDesc->m_pBlockStartAddr != i_ptr && curOutstandingDesc != nullptr)
	{
		prevOutstandingDesc = curOutstandingDesc;
		curOutstandingDesc = curOutstandingDesc->next;
	}
	if(curOutstandingDesc == nullptr)
		return false;
	//guardbanding
#ifdef _DEBUG
	curOutstandingDesc->m_pBlockStartAddr = (unsigned char *)curOutstandingDesc->m_pBlockStartAddr - nNoMansLandSize;
	curOutstandingDesc->m_sizeBlock += 2 * nNoMansLandSize;
#endif // _DEBUG

	//for alignment
	while (*((unsigned char *)curOutstandingDesc->m_pBlockStartAddr - 1) == _bAlignLandFill)
	{
		curOutstandingDesc->m_pBlockStartAddr = (unsigned char *)curOutstandingDesc->m_pBlockStartAddr - 1;
		curOutstandingDesc->m_sizeBlock++;
	}
	//fillvalues
	memset(curOutstandingDesc->m_pBlockStartAddr, _bDeadLandFill, curOutstandingDesc->m_sizeBlock);
	//modify list structure;
	//if it's head
	if (prevOutstandingDesc == nullptr)
	{
		m_OutstandingBlockListHead = m_OutstandingBlockListHead->next;
	}
	else
	{
		prevOutstandingDesc->next = curOutstandingDesc->next;
	}
	//move this desc to free list in their address order
	BlockDescriptor * curFreeBlockDesc = m_FreeBlockListHead, * prevFreeBlockDesc = nullptr;
	//if no free blocks left
	if (curFreeBlockDesc == nullptr)
	{
		m_FreeBlockListHead = curOutstandingDesc;
		m_FreeBlockListHead->next = nullptr;
		return true;
	}
	while (curFreeBlockDesc != nullptr && curFreeBlockDesc->m_pBlockStartAddr < curOutstandingDesc->m_pBlockStartAddr)
	{
		prevFreeBlockDesc = curFreeBlockDesc;
		curFreeBlockDesc = curFreeBlockDesc->next;
	}
	curOutstandingDesc->next = curFreeBlockDesc;
	if (prevFreeBlockDesc == nullptr)
		m_FreeBlockListHead = curOutstandingDesc;
	else
		prevFreeBlockDesc->next = curOutstandingDesc;
	
	return true;
}

void HeapManager::collect()
{
	BlockDescriptor * curFreeBlockDesc = m_FreeBlockListHead, * nextFreeBlockDesc = m_FreeBlockListHead->next, * tailFreeBlockDesc = m_FreeBlockListHead;
	//get the tail for movement
	while (tailFreeBlockDesc->next != nullptr)
		tailFreeBlockDesc = tailFreeBlockDesc->next;
	while (nextFreeBlockDesc != nullptr && nextFreeBlockDesc->m_pBlockStartAddr != nullptr)
	{
		//if two block can be combined. We can do this because free list is stored in their block start address order
		if ((unsigned char *)curFreeBlockDesc->m_pBlockStartAddr + curFreeBlockDesc->m_sizeBlock == nextFreeBlockDesc->m_pBlockStartAddr)
		{
			//add up numbers
			curFreeBlockDesc->m_sizeBlock += nextFreeBlockDesc->m_sizeBlock;
			curFreeBlockDesc->next = nextFreeBlockDesc->next;
			//move next free block to tail for future use
			nextFreeBlockDesc->next = tailFreeBlockDesc->next;
			tailFreeBlockDesc->next = nextFreeBlockDesc;
			nextFreeBlockDesc->m_pBlockStartAddr = nullptr;
			nextFreeBlockDesc->m_sizeBlock = 0;
		}
		else
		{
			curFreeBlockDesc = nextFreeBlockDesc;
		}
		//progression
		nextFreeBlockDesc = curFreeBlockDesc->next;
	}
}

bool HeapManager::Contains(void * i_ptr) const
{
	void * endOfHeap = (unsigned char *)pHeapMemory + sizeHeap;
	void * startOfDescriptors = (unsigned char *)endOfHeap - numDescritors * sizeof(BlockDescriptor);
	BlockDescriptor * curBlockDesc = (BlockDescriptor *)startOfDescriptors;
	for (unsigned int i = 0; i < numDescritors; ++i)
	{
		if (curBlockDesc->m_pBlockStartAddr == i_ptr)
			return true;
		else
			curBlockDesc = curBlockDesc + 1;
	}
	return false;
}

bool HeapManager::IsAllocated(void * i_ptr) const
{
	BlockDescriptor * curOutstandingDesc = m_OutstandingBlockListHead;
	while (curOutstandingDesc->m_pBlockStartAddr != i_ptr && curOutstandingDesc != nullptr)
	{
		curOutstandingDesc = curOutstandingDesc->next;
	}
	if (curOutstandingDesc == nullptr)
		return false;
	else
		return true;
}

size_t HeapManager::getLargestFreeBlock() const
{
	size_t maxSize = 0;
	BlockDescriptor * curFreeBlockDesc = m_FreeBlockListHead;
	while (curFreeBlockDesc->m_pBlockStartAddr != nullptr)
	{
		if (maxSize < curFreeBlockDesc->m_sizeBlock)
		{
			maxSize = curFreeBlockDesc->m_sizeBlock;
		}
		curFreeBlockDesc = curFreeBlockDesc->next;
	}
	return maxSize;
}

size_t HeapManager::getTotalFreeMemory() const
{
	size_t totalSize = 0;
	BlockDescriptor * curFreeBlockDesc = m_FreeBlockListHead;
	while (curFreeBlockDesc->m_pBlockStartAddr != nullptr)
	{
		totalSize += curFreeBlockDesc->m_sizeBlock;
		curFreeBlockDesc = curFreeBlockDesc->next;
	}
	return totalSize;
}

void HeapManager::ShowFreeBlocks() const
{
	BlockDescriptor * curFreeBlockDesc = m_FreeBlockListHead;
	unsigned int count = 0;
	while (curFreeBlockDesc != nullptr && curFreeBlockDesc->m_pBlockStartAddr != nullptr)
	{
		printf("Free Block %d: Start Address: %p, Size: %d \n", count++, curFreeBlockDesc->m_pBlockStartAddr, curFreeBlockDesc->m_sizeBlock);
		curFreeBlockDesc = curFreeBlockDesc->next;
	}
}

void HeapManager::ShowOutstandingAllocations() const
{
	BlockDescriptor * curOutstandingDesc = m_OutstandingBlockListHead;
	unsigned int count = 0;
	while (curOutstandingDesc != nullptr)
	{
		printf("Outstanding Block %d: Start Address: %p, Size: %d \n", count++, curOutstandingDesc->m_pBlockStartAddr, curOutstandingDesc->m_sizeBlock);
		curOutstandingDesc = curOutstandingDesc->next;
	}
}
