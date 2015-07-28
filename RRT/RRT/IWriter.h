#ifndef _IWRITERHEADERGUARD
#define _IWRITERHEADERGUARD

#include "RGBImage.h"

namespace RRT {

	class IWriter {
	public:
		virtual bool write(const RGBImage&, std::ostream& out) = 0;

	};

}

#endif