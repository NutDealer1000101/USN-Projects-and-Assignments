export module MyMath;

import std;

namespace math {
	export template<typename T>
	T Square(const T& n);

	export template<typename T>
	const T& Max(const T& a, const T& b);

	export template<typename T>
	const T& Min(const T& a, const T& b);

	export template<typename T>
	T Sum(const T& a, const T& b);

	export const float shitty_pi{ 3.1f };

	export enum class Oddity { Even, Odd };

	export Oddity GetOddity(int x);
}

bool IsEven(int x) {
	return x % 2 == 0;
}

template<typename T>
T math::Square(const T& n) {
	return n * n;
}

template<typename T>
const T& math::Max(const T& a, const T& b) {
	return a > b ? a : b;
}

template<typename T>
const T& math::Min(const T& a, const T& b) {
	return a < b ? a : b;
}

template<typename T>
T math::Sum(const T& a, const T& b) {
	return a + b;
}

math::Oddity math::GetOddity(int x) {
	return IsEven(x) ? math::Oddity::Even : math::Oddity::Odd;
} 