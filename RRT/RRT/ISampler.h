#ifndef _ISAMPLERHEADERGUARD
#define _ISAMPLERHEADERGUARD

#include <vector>

#include "SimplePoint.h"

namespace RRT {

	template <typename T>
	class ISampler {

	public:

		virtual void Generate(std::vector<SimplePoint2<T>>& samples, size_t number) const = 0;

	};

}
 
#endif