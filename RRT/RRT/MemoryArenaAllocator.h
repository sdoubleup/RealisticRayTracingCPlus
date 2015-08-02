#ifndef _MEMORYARENAHEADERGUARD
#define _MEMORYARENAHEADERGUARD

#include <vector>
#include "AllocAligned.h"

namespace RRT {

	class MemoryArenaAllocator {

	public:
		
		MemoryArenaAllocator(size_t blocksize = 32768);
		~MemoryArenaAllocator();

		void* Alloc(size_t size);
				
		template<typename T>
		T* Alloc(size_t count = 1) {
			T* r = static_cast<T*>(Alloc(count * sizeof(T)));
			for (size_t i = 0; i < count; ++i) { new (&r[i] T()); }
			return r;
		}

		void Free();

	private:

		// Round up to minimum machine alignment.
		// Next multiple of 16.
		size_t Round(size_t size) const;

		void NewBlock(size_t size);

		size_t m_current_block_pos;
		size_t m_block_size;

		char* m_current_block;

		std::vector<char *> m_used;
		std::vector<char *> m_available;

	};


}

#endif