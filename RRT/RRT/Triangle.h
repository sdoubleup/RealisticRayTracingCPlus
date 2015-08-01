#ifndef _TRIANGLEHEADERGUARD
#define _TRIANGLEHEADERGUARD

#include "IShape.h"

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
			T A = pt0().x() - pt1().x();
			T B = pt0().y() - pt1().y();
			T C = pt0().z() - pt1().z();
			
			T D = pt0().x() - pt2().x();
			T E = pt0().y() - pt2().y();
			T F = pt0().z() - pt2().z();

			T G = r.Direction().x();
			T H = r.Direction().y();
			T I = r.Direction().z();

			T J = pt0().x() - r.Origin().x();
			T K = pt0().y() - r.Origin().y();
			T L = pt0().z() - r.Origin().z();

			T EIHF = E * I - H * F;
			T GFDI = G * F - D * I;
			T DHEG = D * H - E * G;

			T denominator = (A * EIHF + B * GFDI + C * DHEG);

			// Not expecting a division by zero here.
			FloatingPoint<T> floatpt_zero(0.0);
			FloatingPoint<T> floatpt_one(1.0);
			FloatingPoint<T> floatpt_deno(denominator);
			assert(floatpt_deno.AlmostEquals(floatpt_zero) == false);
			if (floatpt_deno.AlmostEquals(floatpt_zero)) { return ShapeHitRecord<T>(false, 0.0, m_normal, m_color); }

			T beta = (J * EIHF + K * GFDI + L * DHEG) / denominator;

			FloatingPoint<T> floatpt_beta(beta);
			if (beta < 0.0 || floatpt_beta.AlmostEquals(floatpt_zero) || beta > 1.0 || floatpt_beta.AlmostEquals(floatpt_one)) { 
				return ShapeHitRecord<T>(false, 0.0, m_normal, m_color); 
			}

			T AKJB = A * K - J * B;
			T JCAL = J * C - A * L;
			T BLKC = B * L - K * C;

			T gamma = (I * AKJB + H * JCAL + G * BLKC) / denominator;
			FloatingPoint<T> floatpt_gamma(gamma);
			if (gamma < 0.0 || floatpt_gamma.AlmostEquals(floatpt_zero) || beta + gamma > 1.0 || FloatingPoint<T>(beta + gamma).AlmostEquals(floatpt_one)) { 
				return ShapeHitRecord<T>(false, 0.0, m_normal, m_color); 
			}

			T tval = -(F * AKJB + E * JCAL + D * BLKC) / denominator;
			FloatingPoint<T> floatpt_tval(tval);
			FloatingPoint<T> floatpt_min(parameter_min);
			FloatingPoint<T> floatpt_max(parameter_max);

			bool hit = (tval > parameter_min && tval < parameter_max && !floatpt_tval.AlmostEquals(floatpt_min) && !floatpt_tval.AlmostEquals(floatpt_max));

			return ShapeHitRecord<T>(hit, tval, m_normal, m_color);
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