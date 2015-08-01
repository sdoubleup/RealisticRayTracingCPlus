#ifndef _RAYHEADERGUARD
#define _RAYHEADERGUARD

#include <vector>
#include <assert.h>

#include "Vector3.h"

namespace RRT {
		
	template<typename T>
	class Ray {

	public:

		Ray(const Vector3<T>& origin, const Vector3<T>& direction) {
			m_components.push_back(origin);
			m_components.push_back(direction.Unit());
		}
		Ray(const Ray<T>& other) : m_components(other.m_components) {}

		Vector3<T> Origin() const { return m_components[0]; }
		Vector3<T> Direction() const { return m_components[1]; }

		Vector3<T> PointAtParameter(double t) { return m_components[0] + (t * m_components[1]); }

	private:

		std::vector<Vector3<T>> m_components;

	};

}

#endif
