#ifndef _ISHAPEHEADERGUARD
#define _ISHAPEHEADERGUARD

#include "Ray.h"
#include "RGBColor.h"

namespace RRT {

	// Simple structure to hold hit information.
	// Made to be const once created.
	template<typename T>
	class ShapeHitRecord {

	public:
			
		ShapeHitRecord(bool hit, T parameter, const Vector3<T>& normal, const RGBColor& color) : m_hit(hit), m_parameter(parameter), m_normal(normal), m_color(color) {};

		T Parameter() const { return m_parameter; }
		Vector3<T> Normal() const { return m_normal; }
		RGBColor Color() const { return m_color; }
		bool Hit() const { return m_hit; }

	private:

		T m_parameter;
		Vector3<T> m_normal;
		RGBColor m_color;
		bool m_hit;

	};

	template <typename T>
	class IShape {

	public:

		virtual ShapeHitRecord<T> Hit(const Ray<T>& r, T parameter_min, T parameter_max, T time) const = 0;
		virtual bool ShadowHit(const Ray<T>& r, T parameter_min, T parameter_max, T time) const = 0;

	};

}

#endif
