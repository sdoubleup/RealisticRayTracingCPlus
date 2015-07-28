#ifndef _RGBCOLORHEADERGUARD
#define _RGBCOLORHEADERGUARD

#include <vector>

namespace RRT {

	class RGBColor {

	public:

		RGBColor(double R, double G, double B);
		RGBColor(const RGBColor& c);
		RGBColor(RGBColor&& c);

		double R() const;
		double G() const;
		double B() const;

		RGBColor& operator+=(const RGBColor& rhs);
		RGBColor& operator-=(const RGBColor& rhs);
		RGBColor& operator/=(const RGBColor& rhs);
		RGBColor& operator*=(const RGBColor& rhs);

		RGBColor operator/(const double rhs);
		RGBColor operator*(const double rhs);

		RGBColor& operator=(const RGBColor& rhs);

	private:

		void clamp();

		std::vector<double> m_components;

	};

	inline RGBColor operator+(RGBColor lhs, const RGBColor rhs) {
		lhs += rhs;
		return lhs;
	}

	inline RGBColor operator-(RGBColor lhs, const RGBColor rhs) {
		lhs -= rhs;
		return lhs;
	}

	inline RGBColor operator/(RGBColor lhs, const RGBColor rhs) {
		lhs /= rhs;
		return lhs;
	}

	inline RGBColor operator*(RGBColor lhs, const RGBColor rhs) {
		lhs *= rhs;
		return lhs;
	}
}

#endif