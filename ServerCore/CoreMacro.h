#pragma once

#define CRASH(cause)						\
{											\
	uint32* crash = nullptr;				\
	__analysis_assert(crash != nullptr);	\
	*crash = 0xDEADBEEF;					\
}											

#define ASSERT_CRASH(expr)					\
{											\
	if ((expr) == false)					\
	{										\
		CRASH("ASSERT_CRASH");				\
		__analysis_assert(expr);			\
	}										\
}

#define USE_MANY_LOCK(count)	Lock _lock[count];
#define USE_LOCK				USE_MANY_LOCK(1);
#define READ_LOCK_IDX(idx)		ReadLockGuard readLockGuard_##idx(_lock[idx], typeid(this).name());
#define READ_LOCK				READ_LOCK_IDX(0);
#define WRITE_LOCK_IDX(idx)		WriteLockGuard writeLockGuard_##idx(_lock[idx], typeid(this).name());
#define WRITE_LOCK				WRITE_LOCK_IDX(0);

#ifdef _DEBUG
#define XAlloc(size)			StompAllocator::Alloc(size)
#define XRelease(ptr)			StompAllocator::Release(ptr)
#else
#define XAlloc(size)			PoolAllocator::Alloc(size)
#define XRelease(ptr)			PoolAllocator::Release(ptr)
#endif
