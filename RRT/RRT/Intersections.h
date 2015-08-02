#ifndef _INTERSECTIONSHEADERGUARD
#define _INTERSECTIONSHEADERGUARD

#include "Vector3.h"
#include "Ray.h"
#include "GoogleTestFloatingPoint.h"

namespace RRT {

	class IntersectionTests {

	public :


		// Determine if a ray intersects with a given triangle.
		// Uses the Möller–Trumbore algorithm.
		template <typename T>
		static bool RayTriangle(const Ray<T>& r, const Vector3<T>& pt0, const Vector3<T>& pt1, const Vector3<T>& pt2, T& out) {

			Vector3<T> edge1 = pt1 - pt0;
			Vector3<T> edge2 = pt2 - pt0;

			// Begin calculating determinant - also used to calculate U parameter.
			Vector3<T> P = r.Direction().Cross(edge2);
			// If determinant is near zero, ray lies in plane of triangle
			double determinant = edge1.Dot(P);
			FloatingPoint<double> fp_determinant(determinant);
			FloatingPoint<double> zero(0.0);
			if (fp_determinant.AlmostEquals(zero)) {
				return false;
			}

			double inverse_determinant = 1.0 / determinant;

			// Calculate distance from V1 to ray origin
			Vector3<T> dist_ray_origin = r.Origin() - pt0;

			// Calculate u parameter and test bound
			double u = dist_ray_origin.Dot(P) * inverse_determinant;
			// The intersection lies outside of the triangle
			if (u < 0.0 || u > 1.0) {
				return false;
			}

			// Prepare to test v parameter
			Vector3<T> Q = dist_ray_origin.Cross(edge1);
			// Calculate V parameter and test bound
			double v = r.Direction().Dot(Q) * inverse_determinant;
			// The intersection lies outside of the triangle
			if (v < 0.f || u + v  > 1.f) {
				return false;
			}

			double param = edge2.Dot(Q) * inverse_determinant;

			// Hit.
			FloatingPoint<double> fp_t(param);
			if (!fp_t.AlmostEquals(zero) && !(param < 0.0)) {
				out = param;
				return true;
			}

			// No hit.
			return false;
		}

	};

}

#endif