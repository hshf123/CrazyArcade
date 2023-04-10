#include "pch.h"
#include "MemoryPool.h"

MemoryPool::MemoryPool(int32 allocSize) : _allocSize(allocSize)
{
	::InitializeSListHead(&_header);
}

MemoryPool::~MemoryPool()
{
	while (MemoryHeader* memory = static_cast<MemoryHeader*>(::InterlockedPopEntrySList(&_header)))
		::_aligned_free(memory);
}

void MemoryPool::Push(MemoryHeader* ptr)
{
	ptr->allocSize = 0;

	::InterlockedPushEntrySList(&_header, static_cast<PSLIST_ENTRY>(ptr));

	_useCount--;
	_reserveCount--;
}

MemoryHeader* MemoryPool::Pop()
{
	MemoryHeader* header = static_cast<MemoryHeader*>(::InterlockedPopEntrySList(&_header));

	if (header == nullptr)
	{
		header = reinterpret_cast<MemoryHeader*>(::_aligned_malloc(_allocSize, SLIST_ALIGNMENT));
	}
	else
	{
		ASSERT_CRASH(header->allocSize == 0);
		_reserveCount++;
	}

	_useCount++;

	return header;
}
