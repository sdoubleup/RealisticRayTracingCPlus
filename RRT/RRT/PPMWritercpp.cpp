#include <ostream>
#include <algorithm>

#include "PPMWriter.h"

#define MAXVAL 256

namespace RRT {

	PPMWriter::PPMWriter() {}

	bool PPMWriter::write(const RGBImage& img, std::ostream& out) {
		// Header
		out << "P6\n";
		out << img.Height() << ' ' << img.Width() << '\n';
		out << MAXVAL - 1 << "\n";

		// Gamma adjustment
		double power = 1.0 / img.Gamma();

		// Output clamped [0, 255] values.
		// PPM write in columns across...

		size_t rows = img.Height();
		size_t row_width = img.Width();
		
		// 'i' is int instead of size_t as otherwise it wraps around at 0 - 1 and
		// things go crazy.
		for (int i = rows - 1; i >= 0; --i) {
			for (size_t j = 0; j < row_width; ++j) {
				const RGBColor col = img.Pixel(j, i);
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