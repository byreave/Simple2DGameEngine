#pragma once

class HeapManager {
	struct BlockDescriptor {
		void * m_pBlockStartAddr;
		size_t m_sizeBlock;
		BlockDescriptor * next;
	};

public:
	static HeapManager * create(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors);
	void destroy();
	void * _alloc(size_t i_size);
	void * _alloc(size_t i_size, size_t i_alignment);
	bool _free(void * i_ptr);
	void collect();
	bool Contains(void * i_ptr) const;
	bool IsAllocated(void * i_ptr) const;
	size_t getLargestFreeBlock() const;
	size_t getTotalFreeMemory() const;
	void ShowFreeBlocks() const;
	void ShowOutstandingAllocations() const;


private:
	BlockDescriptor * m_FreeBlockListHead;
	BlockDescriptor * m_OutstandingBlockListHead;

	void * pHeapMemory;
	size_t sizeHeap;
	unsigned int numDescritors;
};