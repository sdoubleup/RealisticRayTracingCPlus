#ifndef _ALLOCALIGNEDHEADERGUARD
#define _ALLOCALIGNEDHEADERGUARD

#ifndef _L1_CACHE_LINE_SIZE
#define _L1_CACHE_LINE_SIZE 64
#endif

#include <malloc.h>

void* AllocAligned(size_t size) {
	return _aligned_malloc(size, _L1_CACHE_LINE_SIZE);
}

template <typename T>
T* AllocAligned(size_t count) {
	return static_cast<T*>(AllocAligned(count * sizeof(T)));
}

void FreeAligned(void* ptr) {
	_aligned_free(ptr);
}

#endif