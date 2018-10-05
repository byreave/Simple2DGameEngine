#include "HeapManager.h"
#include <stdint.h>

HeapManager * HeapManager::create(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
{
	void * endOfHeap = (char *)i_pMemory + i_sizeMemory;
	void * startOfDescriptors = (char *)endOfHeap - i_numDescriptors * sizeof(BlockDescriptor);
	//Put heapmanager before descriptors
	HeapManager * heapManager = (HeapManager *)((char *)startOfDescriptors - sizeof(HeapManager));
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
	heapManager->m_FreeBlockListTail = heapManager->m_FreeBlockListHead->next;
	//last descriptor
	tmp->next = nullptr;
	return heapManager;
}

void HeapManager::destroy()
{
}

void * HeapManager::_alloc(size_t i_size)
{
	//if (m_FreeBlockListHead == nullptr)
	//	return nullptr;
	BlockDescriptor * curFreeBlock = m_FreeBlockListHead;
	BlockDescriptor * prevFreeBlock = nullptr;
	while (curFreeBlock->m_sizeBlock < i_size && curFreeBlock != nullptr)
	{
		prevFreeBlock = curFreeBlock;
		curFreeBlock = curFreeBlock->next;
	}

	if (curFreeBlock == nullptr)
		return nullptr;
	//exactly the size
	if (curFreeBlock->m_sizeBlock == i_size)
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
		//not enough descriptors
		if (m_FreeBlockListTail == nullptr)
		{
			m_FreeBlockListHead = nullptr;
		}
		//when it is the free block list head
		if (prevFreeBlock == nullptr)
		{
			m_FreeBlockListHead = m_FreeBlockListTail;
			m_FreeBlockListTail = m_FreeBlockListTail->next;
			m_FreeBlockListHead->m_sizeBlock = curFreeBlock->m_sizeBlock - i_size;
			m_FreeBlockListHead->m_pBlockStartAddr = (char *)curFreeBlock->m_pBlockStartAddr + i_size;
			if (m_FreeBlockListHead->next == curFreeBlock->next) //Tail is the next of head
				m_FreeBlockListHead->next = m_FreeBlockListTail;
			else
				m_FreeBlockListHead->next = curFreeBlock->next;

		}
		else
		{
			prevFreeBlock->next = m_FreeBlockListTail;
			m_FreeBlockListTail = m_FreeBlockListTail->next;
			prevFreeBlock->next->m_sizeBlock = curFreeBlock->m_sizeBlock - i_size;
			prevFreeBlock->next->m_pBlockStartAddr = (char *)curFreeBlock->m_pBlockStartAddr + i_size;
			prevFreeBlock->next->next = curFreeBlock->next;
		}
	}
	curFreeBlock->next = m_OutstandingBlockListHead;
	curFreeBlock->m_sizeBlock = i_size;
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
		alignAddr = curFreeBlock->m_pBlockStartAddr;
		while ((reinterpret_cast<uintptr_t>(alignAddr) & (i_alignment - 1)) != 0)
		{
			alignAddr = (char *)alignAddr + 1;
			alignOffset++;
		}
		if (curFreeBlock->m_sizeBlock - alignOffset >= i_size)
			break;
		prevFreeBlock = curFreeBlock;
		curFreeBlock = curFreeBlock->next;
	}
	//to do: add free block for alignment;

	if (curFreeBlock == nullptr)
		return nullptr;
	//exactly the size
	if (curFreeBlock->m_sizeBlock == i_size)
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
		//not enough descriptors
		if (m_FreeBlockListTail == nullptr)
		{
			m_FreeBlockListHead = nullptr;
		}
		//when it is the free block list head
		if (prevFreeBlock == nullptr)
		{
			m_FreeBlockListHead = m_FreeBlockListTail;
			m_FreeBlockListTail = m_FreeBlockListTail->next;
			m_FreeBlockListHead->m_sizeBlock = curFreeBlock->m_sizeBlock - i_size;
			m_FreeBlockListHead->m_pBlockStartAddr = (char *)curFreeBlock->m_pBlockStartAddr + i_size;
			if (m_FreeBlockListHead->next == curFreeBlock->next) //Tail is the next of head
				m_FreeBlockListHead->next = m_FreeBlockListTail;
			else
				m_FreeBlockListHead->next = curFreeBlock->next;

		}
		else
		{
			prevFreeBlock->next = m_FreeBlockListTail;
			m_FreeBlockListTail = m_FreeBlockListTail->next;
			prevFreeBlock->next->m_sizeBlock = curFreeBlock->m_sizeBlock - i_size;
			prevFreeBlock->next->m_pBlockStartAddr = (char *)curFreeBlock->m_pBlockStartAddr + i_size;
			prevFreeBlock->next->next = curFreeBlock->next;
		}
	}
	curFreeBlock->next = m_OutstandingBlockListHead;
	curFreeBlock->m_sizeBlock = i_size;
	m_OutstandingBlockListHead = curFreeBlock;
	return curFreeBlock->m_pBlockStartAddr;
}

bool HeapManager::_free(void * i_ptr)
{
	return false;
}

void HeapManager::collect()
{
}

bool HeapManager::Contains(void * i_ptr) const
{
	return false;
}

bool HeapManager::IsAllocated(void * i_ptr) const
{
	return false;
}

size_t HeapManager::getLargestFreeBlock() const
{
	return size_t();
}

size_t HeapManager::getTotalFreeMemory() const
{
	return size_t();
}

void HeapManager::ShowFreeBlocks() const
{
}

void HeapManager::ShowOutstandingAllocations() const
{
}
