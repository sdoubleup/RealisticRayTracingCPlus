#ifndef _ORTHONORMALBASISHEADERGUARD
#define _ORTHONORMALBASISHEADERGUARD

#include "Vector3.h"

#define ONB_EPSILON 0.01

namespace RRT {

	template<typename T>
	class OrthonormalBasis {
		
	public:

		OrthonormalBasis(const Vector3<T>& u, const Vector3<T>& v, const Vector3<T>& w) : m_u(u), m_v(v), m_w(w) {};

		OrthonormalBasis(const OrthonormalBasis<T>& other) : m_u(other.m_u), m_v(other.m_v), m_w(other.m_w) {};

		OrthonormalBasis<T>& operator=(const OrthonormalBasis<T>& other) {
			m_u = other.m_u;
			m_v = other.m_v;
			m_w = other.m_w;
			return *this;
		}
		
		static OrthonormalBasis<T> FromU(const Vector3<T>& u) {
			Vector3<T> n(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));
			Vector3<T> m(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));
			Vector3<T> unit_u = u.Unit();
			Vector3<T> v = unit_u.Cross(n);
			if (v.Length() < ONB_EPSILON) {
				v = unit_u.Cross(m);
			}
			Vector3<T> w = unit_u.Cross(v);
			return OrthonormalBasis<T>(unit_u, v, w);
		}

		static OrthonormalBasis<T> FromV(const Vector3<T>& v) {
			Vector3<T> n(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));
			Vector3<T> m(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));
			Vector3<T> unit_v = v.Unit();
			Vector3<T> u = unit_v.Cross(n);
			if ((u.Length() * u.Length()) < ONB_EPSILON) {
				u = unit_v.Cross(m);
			}
			Vector3<T> w = u.Cross(unit_v);
			return OrthonormalBasis<T>(u, unit_v, w);
		}

		static OrthonormalBasis<T> FromW(const Vector3<T>& w) {
			Vector3<T> n(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));
			Vector3<T> m(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));
			Vector3<T> unit_w = w.Unit();
			Vector3<T> u = unit_w.Cross(n);
			if (u.Length() < ONB_EPSILON) {
				u = unit_w.Cross(m);
			}
			Vector3<T> v = unit_w.Cross(u);
			return OrthonormalBasis<T>(u, v, unit_w);
		}

		static OrthonormalBasis<T> FromUV(const Vector3<T>& u, const Vector3<T>& v) {
			Vector3<T> _U = u.Unit();
			Vector3<T> _W = u.Cross(v).Unit();
			Vector3<T> _V = _W.Cross(_U);
			return OrthonormalBasis<T>(_U, _W, _V);
		}

		static OrthonormalBasis<T> FromVU(const Vector3<T>& v, const Vector3<T>& u) {
			Vector3<T> _V = v.Unit();
			Vector3<T> _W = u.Cross(v).Unit();
			Vector3<T> _U = _V.Cross(_W);
			return OrthonormalBasis<T>(_U, _W, _V);
		}

		static OrthonormalBasis<T> FromUW(const Vector3<T>& u, const Vector3<T>& w) {
			Vector3<T> _U = u.Unit();
			Vector3<T> _V = w.Cross(u).Unit();
			Vector3<T> _W = _U.Cross(_V);
			return OrthonormalBasis<T>(_U, _W, _V);
		}

		static OrthonormalBasis<T> FromWU(const Vector3<T>& w, const Vector3<T>& u) {
			Vector3<T> _W = w.Unit();
			Vector3<T> _V = w.Cross(u).Unit();
			Vector3<T> _U = _V.Cross(_W);
			return OrthonormalBasis<T>(_U, _W, _V);
		}

		static OrthonormalBasis<T> FromVW(const Vector3<T>& v, const Vector3<T>& w) {
			Vector3<T> _V = v.Unit();
			Vector3<T> _U = v.Cross(w).Unit();
			Vector3<T> _W = _U.Cross(_V);
			return OrthonormalBasis<T>(_U, _W, _V);
		}

		static OrthonormalBasis<T> FromWV(const Vector3<T>& w, const Vector3<T>& v) {
			Vector3<T> _W = w.Unit();
			Vector3<T> _U = v.Cross(w).Unit();
			Vector3<T> _V = _W.Cross(_U);
			return OrthonormalBasis<T>(_U, _W, _V);
		}

		Vector3<T> u() const { return m_u; }
		Vector3<T> v() const { return m_v; }
		Vector3<T> w() const { return m_w; }

		bool Equals(const OrthonormalBasis<T>& other) {
			return (m_u.Equals(other.m_u) && m_v.Equals(other.m_v) && m_w.Equals(other.m_w));
		}

	private:

		Vector3<T> m_u;
		Vector3<T> m_v;
		Vector3<T> m_w;

	};

}

#endif