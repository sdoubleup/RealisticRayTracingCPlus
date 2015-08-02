#include "MemoryArenaAllocator.h"

#include <algorithm>

namespace RRT {

	MemoryArenaAllocator::MemoryArenaAllocator(size_t blocksize) {
		m_block_size = blocksize;
		m_current_block_pos = 0;
		m_current_block = AllocAligned<char>(m_block_size);
	}

	MemoryArenaAllocator::~MemoryArenaAllocator() {}

	void* MemoryArenaAllocator::Alloc(size_t size) {
		size_t rounded = Round(size);
		// If there isn't enough space on this block, we need to
		// allocate a new one.
		if (m_current_block_pos + rounded > m_block_size) {
			NewBlock(rounded);
			m_current_block_pos = 0;
		}
		void* r = m_current_block + m_current_block_pos;
		m_current_block_pos += rounded;
		return r;
	}

	void MemoryArenaAllocator::Free() {
		m_current_block_pos = 0;
		while (m_used.size()) {
			m_available.push_back(m_used.back());
			m_used.pop_back();
		}
	}

	size_t MemoryArenaAllocator::Round(size_t size) const {
		return ((size + 15) & (~15));
	}

	void MemoryArenaAllocator::NewBlock(size_t size) {
		m_used.push_back(m_current_block);
		if (m_available.size() && size <= m_block_size) {
			m_current_block = m_available.back();
			m_available.pop_back();
		} else {
			m_current_block = AllocAligned<char>(std::max(size, m_block_size));
		}
	}

}