#include <assert.h>
#include <algorithm>

#include "RGBImage.h"



namespace RRT {

	RGBImage::RGBImage(size_t width, size_t height) : RGBImage(width, height, RGBColor(1.0, 0.0, 0.0)) {}

	RGBImage::RGBImage(size_t width, size_t height, RGBColor initialise) : m_gamma(1.0), m_h(height), m_w(width) {
		assert(width > 0);
		assert(height > 0);
		m_raster.reserve(height);
		for (size_t i = 0; i < height; i++) {
			m_raster.push_back(std::vector<RGBColor>(width, initialise));
		}
	}

	bool RGBImage::SetRow(size_t index, std::vector<RGBColor>& row) {
		assert(index < m_h);
		m_raster[index] = row;
		return true;
	}

	bool RGBImage::SetPixel(size_t row, size_t col, RGBColor& color) {
		assert(row < m_h);
		assert(col < m_w);
		m_raster[row][col] = color;
		return true;
	}

	void RGBImage::SetGamma(double gamma) {
		assert(gamma > 0.0);
		m_gamma = gamma;
	}

	double RGBImage::Gamma() const {
		return m_gamma;
	}

	RGBColor RGBImage::Pixel(size_t row, size_t column) const {
		assert(row < m_h);
		assert(column < m_w);
		return (m_raster[row])[column];
	}

	std::vector<RGBColor> RGBImage::RowCopy(size_t r) const {
		assert(r < m_h);
		return m_raster[r];
	}

	const std::vector<RGBColor>& RGBImage::ConstRow(size_t r) const {
		assert(r < m_h);
		return m_raster[r];
	}

	std::vector<RGBColor>& RGBImage::ModifiableRow(size_t r) {
		assert(r < m_h);
		return m_raster[r];
	}
}