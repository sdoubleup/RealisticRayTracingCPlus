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
		// Dimensions
		//
		size_t Height() const { return m_h; }
		size_t Width() const { return m_w; }

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

		//
		// Gamma
		//
		double Gamma() const;

		//
		// Get the pixel at the location requested.
		//
		RGBColor Pixel(size_t row, size_t column) const;

		//
		// Row accessors.
		// Various speed and safety versions.
		//
		std::vector<RGBColor> RowCopy(size_t r) const;
		const std::vector<RGBColor>& ConstRow(size_t r) const;
		std::vector<RGBColor>& ModifiableRow(size_t r);
		
	private:

		std::vector<std::vector<RGBColor>> m_raster;

		double m_gamma;

		size_t m_h;
		size_t m_w;

	};

}

#endif
