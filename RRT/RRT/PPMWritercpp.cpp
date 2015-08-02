#include <ostream>
#include <algorithm>

#include "PPMWriter.h"

#define MAXVAL 256

namespace RRT {

	PPMWriter::PPMWriter() {}

	bool PPMWriter::write(const RGBImage& img, std::ostream& out) {
		// Header
		out << "P6\n";
		out << img.m_raster.size() << ' ' << img.m_raster[0].size() << '\n';
		out << MAXVAL - 1 << "\n";

		// Gamma adjustment
		double power = 1.0 / img.m_gamma;

		// Output clamped [0, 255] values.
		for (auto row = img.m_raster.begin(); row != img.m_raster.end(); row++) {
			for (auto& col : *row) {
				unsigned int red = std::min(static_cast<int>(MAXVAL * (std::pow(col.R(), power))), MAXVAL - 1);
				unsigned int gre = std::min(static_cast<int>(MAXVAL * (std::pow(col.G(), power))), MAXVAL - 1);
				unsigned int blu = std::min(static_cast<int>(MAXVAL * (std::pow(col.B(), power))), MAXVAL - 1);
				out.put(static_cast<unsigned char>(red));
				out.put(static_cast<unsigned char>(gre));
				out.put(static_cast<unsigned char>(blu));
			}
		}

		return true;
	}


}