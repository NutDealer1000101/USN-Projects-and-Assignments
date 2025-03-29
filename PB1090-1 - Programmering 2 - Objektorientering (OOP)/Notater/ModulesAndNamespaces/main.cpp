import MyMath;

import std;

int main() {
	int a{ 4 };
	int b{ 9 };

	std::println("{} squared is {}", a, math::Square(a));

	std::println("Minimum of {} and {} is {}", a, b, math::Min(a, b));
	std::println("Maximum of {} and {} is {}", a, b, math::Max(a, b));

	std::println("{} + {} = {}", a, b, math::Sum(a, b));

	std::println("First Price pi: {}", math::shitty_pi);

	if (math::GetOddity(a) == math::Oddity::Even) {
		std::println("{} is even", a);
	}
	else {
		std::println("{} is odd", a);
	}

	if (math::GetOddity(b) == math::Oddity::Even) {
		std::println("{} is even", b);
	}
	else {
		std::println("{} is odd", b);
	}

	return 0;
}