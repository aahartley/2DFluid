#pragma once
#include <math.h>

template<typename T>
class Vec3 {
public:
	Vec3(): x(T(0)), y(T(0)), z(T(0)) {}
	Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) { };
	~Vec3() {}

	T magnitude() {
		return ::sqrt(x*x + y*y + z*z);
	}

	T dot(const Vec3<T>& v) {
		return x * v.x + y * v.y + z * v.z;
	}
	Vec3<T> cross(const Vec3<T>& v) {

		return Vec3<T>((y * v.z - z * v.y), -(x * v.z - z * v.x), (x * v.y - y * v.x));
	}
	Vec3<T>& normalize() {
		T len = magnitude();
		if (len > 0) {
			T invL = 1 / len;
			x *= invL, y *= invL, z *= invL;
		}
		return *this;
	}

	Vec3<T> operator+(const Vec3<T>& v) {
		return Vec3<T>(x + v.x, y + v.y, z + v.z);
	}
	Vec3<T> operator-(const Vec3<T>& v) {
		return Vec3<T>(x - v.x, y - v.y, z - v.z);
	}
	Vec3<T> operator*(const T& s) {
		return Vec3<T>(x * s, y *s, z *s);
	}

	Vec3<T>& operator+=(const Vec3<T>& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	T x, y, z;
};

typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;
