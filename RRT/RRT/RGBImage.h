#ifndef _RGBIMAGEHEADERGUARD
#define _RGBIMAGEHEADERGUARD

#include <vector>

#include "RGBColor.h"


namespace RRT {

	class RGBImage {

	public:

		//
		// By default will initialise to white background.
		//
		RGBImage(size_t width, size_t height);
		RGBImage(size_t width, size_t height, RGBColor initialise);
				
		//
		// Set with un-corrected RGB values.
		//
		bool SetRow(size_t index, std::vector<RGBColor>& row);
		bool SetPixel(size_t row, size_t col, RGBColor& color);

		//
		// Set the gamma correction. This is only applied
		// on output write.
		//
		void SetGamma(double gamma);
			
		std::vector<std::vector<RGBColor>> m_raster;

		double m_gamma;

	};

}

#endif
