#ifndef _PPMWRITERHEADERGUARD
#define _PPMWRITERHEADERGUARD

#include "IWriter.h"

namespace RRT {

	class PPMWriter : public IWriter {

	public:

		PPMWriter();

		virtual bool write(const RGBImage& img, std::ostream& out);

	};

}

#endif
