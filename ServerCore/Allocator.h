#pragma once

class StompAllocator
{
	enum { PAGE_SIZE = 0x1000 };

public:
	static void* Alloc(int32 size);
	static void Release(void* ptr);
};

class PoolAllocator
{
public:
	static void* Alloc(int32 size);
	static void Release(void* ptr);
};

template<class T>
class STLAllocator
{
public:
	using value_type = T;

	STLAllocator() { }
	template<class Other>
	STLAllocator(const STLAllocator<Other>&) { }

	T* allocate(size_t count)
	{
		const int32 size = static_cast<int32>(count * sizeof(T));
		return static_cast<T*>(XAlloc(size));
	}

	void deallocate(T* ptr, size_t count)
	{
		XRelease(ptr);
	}
};
