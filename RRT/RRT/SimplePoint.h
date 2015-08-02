#ifndef _SIMPLEPOINTHEADERGUARD
#define _SIMPLEPOINTHEADERGUARD

namespace RRT {

	template <typename T>
	struct SimplePoint2 
	{
		T x;
		T y;

		SimplePoint2(const T& ix, const T& iy) : x(ix), y(iy) {}
	};

	template <typename T>
	struct SimplePoint3
	{
		T x;
		T y;
		T z;

		SimplePoint3(const T& ix, const T& iy, const T& iz) : x(ix), y(iy), z(iz) {}
	};

}

#endif
