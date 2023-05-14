#pragma once
#include <math.h>

template<typename T>
class Vec2 {
public:
	Vec2() : x(T(0)), y(T(0)) {}
	Vec2(T xx, T yy) : x(xx), y(yy) { };
	~Vec2() {}

	T magnitude() {
		return ::sqrt(x * x + y * y);
	}

	T dot(const Vec2<T>& v) {
		return x * v.x + y * v.y;
	}
	//Vec2<T> cross(const Vec3<T>& v) {

	//	return Vec3<T>((y * v.z - z * v.y), -(x * v.z - z * v.x), (x * v.y - y * v.x));
	//}
	Vec2<T>& normalize() {
		T len = magnitude();
		if (len > 0) {
			T invL = 1 / len;
			x *= invL, y *= invL;
		}
		return *this;
	}
	Vec2<T> normal() {
		T len = magnitude();
		if (len > 0) {
			T invL = 1 / len;
			x *= invL, y *= invL;
		}
		return Vec2<T>(x, y);
	}

	Vec2<T> operator+(const Vec2<T>& v) {
		return Vec2<T>(x + v.x, y + v.y);
	}
	Vec2<T> operator-(const Vec2<T>& v) {
		return Vec2<T>(x - v.x, y - v.y);
	}
	Vec2<T> operator*(const T& s) {
		return Vec2<T>(x * s, y * s);
	}

	Vec2<T>& operator+=(const Vec2<T>& v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	T x, y;
};

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
