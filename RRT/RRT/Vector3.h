#ifndef _VECTOR3HEADERGUARD
#define _VECTOR3HEADERGUARD

#include <algorithm>
#include <vector>
#include <assert.h>

namespace RRT {

	template<class T>
	class Vector3 {

	public:

		Vector3(T a, T b, T c) {
			m_components.push_back(a);
			m_components.push_back(b);
			m_components.push_back(c);
		}

		Vector3(const Vector3& other) { *this = other; }

		T x() const { return m_components[0]; }
		T y() const { return m_components[1]; }
		T z() const { return m_components[2]; }

		const Vector3<T>& operator+() const { return *this; }
		Vector3<T>& operator-() const { return Vector3<T>(-m_components[0], -m_components[1], -m_components[2]); }
		Vector3<T>& operator=(const Vector3<T>& v2) { 
			m_components = v2.m_components; 
			return *this;
		}

		template <typename Scalar>
		Vector3<T>& operator*=(const Scalar& scalar) { 
			m_components[0] *= scalar;
			m_components[1] *= scalar;
			m_components[2] *= scalar;
			return *this;
		}

		template <typename Scalar>
		Vector3<T>& operator/=(const Scalar& scalar) {
			m_components[0] /= scalar;
			m_components[1] /= scalar;
			m_components[2] /= scalar;
			return *this;
		}

		Vector3<T>& operator+=(const Vector3<T>& v2) {
			m_components[0] += v2.m_components[0];
			m_components[1] += v2.m_components[1];
			m_components[2] += v2.m_components[2];
			return *this;
		}
		Vector3<T>& operator-=(const Vector3<T>& v2) {
			m_components[0] -= v2.m_components[0];
			m_components[1] -= v2.m_components[1];
			m_components[2] -= v2.m_components[2];
			return *this;
		}

		double Length() const {
			return std::sqrt(
					(m_components[0] * m_components[0]) +
					(m_components[1] * m_components[1]) +
					(m_components[2] * m_components[2])
			);
		}

		Vector3<T> Unit() const { 
			Vector3<T> v(*this);
			v /= v.Length();
			return v;
		}

		Vector3<T> Cross(const Vector3<T> v2) const {
			Vector3<T> t(
				y() * v2.z() - z() * v2.y(),
				z() * v2.x() - x() * v2.z(),
				x() * v2.y() - y() * v2.x()
			);
			return t;
		}

		double Dot(const Vector3<T>& v2) const {
			return x() * v2.x() + y() * v2.y() + z() * v2.z();
		}

		T MinComponent() { return std::min(std::min(x(), y()), z()); }
		T MaxComponent() { return std::max(std::max(x(), y()), z()); }

		T MinAbsolouteComponent() { 
			return std::min(
				std::min(std::fabs(x()), std::fabs(y())),
				std::fabs(z())
			); 
		}
		T MaxAbsolouteComponent() { 
			return std::max(
				std::max(std::fabs(x()), std::fabs(y())), 
				std::fabs(z())
			); 
		}

		// A generalised equality function. This is needed because
		// we can't directly compare floating point values. We have
		// to use an epsilon.
		// Note that the int version is specialised below as the 
		// tolerance is not needed there.
		bool Equals(const Vector3<T>& v2, double tolerance) {
			// Absoloute tolerance, TODO change to a relative or 
			// use the Lexographical nature of floating point?
			// Is relative more appropriate here?
			// Does lexographical work with 64bit?
			if (std::fabs(x() - v2.x()) > tolerance) return false;
			if (std::fabs(y() - v2.y()) > tolerance) return false;
			if (std::fabs(z() - v2.z()) > tolerance) return false;
			return true;
		}

	private:

		std::vector<T> m_components;

	};

	// Specialize on int so that we can handle it more sensibly.
	template <>
	bool Vector3<int>::Equals(const Vector3<int>& v2, double tolerance) {
		return ((x() == v2.x()) && (y() == v2.y()) && (z() == v2.z()));
	}

	template<class T>
	Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2) {
		Vector3<T> t(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
		return t;
	}

	template<class T>
	Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2) {
		Vector3<T> t(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
		return t;
	}

	template<class T>
	Vector3<T> operator*(const Vector3<T>& v1, double scalar) {
		Vector3<T> t(v1.x() * scalar, v1.y() * scalar, v1.z() * scalar);
		return t;
	}

	template<class T, typename Scalar>
	Vector3<T> operator*(const Scalar& scalar, const Vector3<T>& v1) {
		Vector3<T> t(v1.x() * scalar, v1.y() * scalar, v1.z() * scalar);
		return t;
	}

}

#endif
