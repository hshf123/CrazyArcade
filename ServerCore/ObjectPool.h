#pragma once

#include "Types.h"
#include "MemoryPool.h"

template<class Type>
class ObjectPool
{
public:
	template<class... Args>
	static Type* Pop(Args&&... args)
	{
#ifdef _STOMP
		MemoryHeader* ptr = reinterpret_cast<MemoryHeader*>(StompAllocator::Alloc(s_allocSize));
		Type* memory = static_cast<Type*>(MemoryHeader::AttachHeader(ptr, s_allocSize));
#else
		Type* memory = static_cast<Type*>(MemoryHeader::AttachHeader(s_pool.Pop(), s_allocSize));
#endif
		new(memory)Type(forward<Args>(args)...);
		return memory;
	}

	static void Push(Type* obj)
	{
		obj->~Type();
#ifdef _STOMP
		StompAllocator::Release(MemoryHeader::DetachHeader(obj));
#else
		s_pool.Push(MemoryHeader::DetachHeader(obj));
#endif
	}

	template<class... Args>
	static shared_ptr<Type> MakeShared(Args&&... args)
	{
		shared_ptr<Type> ptr = { Pop(forward<Args>(args)...), Push };
		return ptr;
	}

private:
	static int32 s_allocSize;
	static MemoryPool s_pool;
};

template<class Type>
int32 ObjectPool<Type>::s_allocSize = sizeof(Type) + sizeof(MemoryHeader);

template<class Type>
MemoryPool ObjectPool<Type>::s_pool{ s_allocSize };