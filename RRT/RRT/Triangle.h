#ifndef _TRIANGLEHEADERGUARD
#define _TRIANGLEHEADERGUARD

#include "IShape.h"
#include "Intersections.h"

namespace RRT {

	template<typename T>
	class Triangle : public IShape<T> {

	public:

		Triangle(const Vector3<T>& pt0, const Vector3<T>& pt1, const Vector3<T>& pt2, const RGBColor& col) 
			: m_color(col), 
			  m_a(pt0), 
			  m_b(pt1), 
			  m_c(pt2),
			  m_normal((pt1 - pt0).Cross((pt2 - pt0)).Unit()) {}

		virtual ShapeHitRecord<T> Hit(const Ray<T>& r, T parameter_min, T parameter_max, T time) const {
			double param = 0.0;
			bool hit = IntersectionTests::RayTriangle<double>(r, m_a, m_b, m_c, param);
			hit = hit && (param >= parameter_min && param <= parameter_max);
			return ShapeHitRecord<T>(hit, param, m_normal, m_color);
		}

		virtual bool ShadowHit(const Ray<T>& r, T parameter_min, T parameter_max, T time) const {
			return Hit(r, parameter_min, parameter_max, time).Hit();
		}

	private:

		const Vector3<T>& pt0() const { return m_a; }
		const Vector3<T>& pt1() const { return m_b; }
		const Vector3<T>& pt2() const { return m_c; }
		
		Vector3<T> m_a;
		Vector3<T> m_b;
		Vector3<T> m_c;

		RGBColor m_color;

		Vector3<T> m_normal;

	};
	
}

#endif