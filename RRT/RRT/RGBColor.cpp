#include <assert.h>
#include <algorithm>

#include "RGBColor.h"

namespace RRT {

	RGBColor::RGBColor(double R, double G, double B) {
		m_components.reserve(3);
		m_components.push_back(R);
		m_components.push_back(G);
		m_components.push_back(B);
		clamp();
	}

	RGBColor::RGBColor(const RGBColor& c) {
		m_components = c.m_components;
	}

	RGBColor::RGBColor(RGBColor&& c) {
		m_components = std::move(c.m_components);
	}

	double RGBColor::R() const {
		return m_components[0];
	}

	double RGBColor::G() const {
		return m_components[1];
	}

	double RGBColor::B() const {
		return m_components[2];
	}

	RGBColor& RGBColor::operator+=(const RGBColor& rhs) {
		m_components[0] += rhs.m_components[0];
		m_components[1] += rhs.m_components[1];
		m_components[2] += rhs.m_components[2];
		clamp();
		return *this;
	}

	RGBColor& RGBColor::operator-=(const RGBColor& rhs) {
		m_components[0] -= rhs.m_components[0];
		m_components[1] -= rhs.m_components[1];
		m_components[2] -= rhs.m_components[2];
		clamp();
		return *this;
	}

	RGBColor& RGBColor::operator/=(const RGBColor& rhs) {
		assert(m_components[0] != 0.0);
		assert(m_components[1] != 0.0);
		assert(m_components[2] != 0.0);
		m_components[0] /= rhs.m_components[0];
		m_components[1] /= rhs.m_components[1];
		m_components[2] /= rhs.m_components[2];
		clamp();
		return *this;
	}

	RGBColor& RGBColor::operator*=(const RGBColor& rhs) {
		m_components[0] *= rhs.m_components[0];
		m_components[1] *= rhs.m_components[1];
		m_components[2] *= rhs.m_components[2];
		clamp();
		return *this;
	}

	RGBColor RGBColor::operator/(const double rhs) {
		assert(rhs != 0.0);
		return RGBColor(m_components[0] / rhs,
						m_components[1] / rhs,
						m_components[2] / rhs);
	}

	RGBColor RGBColor::operator*(const double rhs) {
		return RGBColor(m_components[0] * rhs,
						m_components[1] * rhs,
						m_components[2] * rhs);
	}

	RGBColor& RGBColor::operator=(const RGBColor& rhs) {
		m_components = rhs.m_components;
		return *this;
	}

	void RGBColor::clamp() {
		m_components[0] = std::max(0.0, std::min(m_components[0], 1.0));
		m_components[1] = std::max(0.0, std::min(m_components[1], 1.0));
		m_components[2] = std::max(0.0, std::min(m_components[2], 1.0));
	}

}