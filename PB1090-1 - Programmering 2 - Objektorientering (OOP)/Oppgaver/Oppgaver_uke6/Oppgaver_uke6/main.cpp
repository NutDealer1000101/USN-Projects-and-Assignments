import std;
#include <assert.h>

template<typename T>
T Clamp(const T& value, const T& min, const T& max) {
	if (value > max) return max;
	if (value < min) return min;
	return value;
}

void oppg10_1() {
	assert(Clamp(5, 0, 10) == 5);
	assert(Clamp(-5, 0, 10) == 0);
	assert(Clamp(15, 0, 10) == 10);

	assert(Clamp(5.0f, 0.0f, 10.0f) == 5.0f);
	assert(Clamp(-5.0f, 0.0f, 10.0f) == 0.0f);
	assert(Clamp(15.0f, 0.0f, 10.0f) == 10.0f);
}

auto Plus(const auto& a, const auto& b) {
	return a + b;
}

auto Plus(auto* pa, auto* pb) {
	return *pa + *pb;
}

std::string Plus(const char* a, const char* b) {
	return std::string(a) + b;
}

void oppg10_3() {
	int a = 2;
	float b = 4.0f;

	assert(Plus(2, 5) == 7);

	assert(Plus(a, b) == 6.0f);
	assert(Plus(&a, &b) == 6.0f);

	std::string c = "Amo";
	assert(Plus(c, "gus") == "Amogus");
} 

int main() {
	//oppg10_1();
	oppg10_3();

	return 0;
}