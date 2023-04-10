#pragma once

#include "Allocator.h"
#include "MemoryPool.h"

class Memory
{
	enum
	{
		POOL_COUNT = (1024 / 32) + (1024 / 128) + (2048 / 256),
		MAX_ALLOC_SIZE = 4096
	};

public:
	Memory();
	~Memory();

	void* Allocate(int32 size);
	void Release(void* ptr);

private:
	vector<MemoryPool*> _pools;
	MemoryPool* _poolTable[MAX_ALLOC_SIZE + 1];
};

template<class Type, class... Args>
Type* xnew(Args&&... args)
{
	Type* memory = static_cast<Type*>(XAlloc(sizeof(Type)));
	new(memory)Type(forward<Args>(args)...);
	return memory;
}

template<class Type>
void xdelete(Type* ptr)
{
	ptr->~Type();
	XRelease(ptr);
}

template<class Type, class... Args>
shared_ptr<Type> MakeShared(Args&&... args)
{
	return shared_ptr<Type>{ xnew<Type>(forward<Args>(args)...), xdelete<Type> };
}