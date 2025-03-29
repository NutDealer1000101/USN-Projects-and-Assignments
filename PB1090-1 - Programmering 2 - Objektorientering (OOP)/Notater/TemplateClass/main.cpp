import std;

#include "Array.h"

int main() {
	Array<int> test{ 10, 20, 30 };

	for (int n : test) {
		std::println("{}", n);
	}
	try {
		int bad = test[69];
	}
	catch (const std::out_of_range& e) {
		std::println("{}", e.what());
	}

	Array<int> test_copy = test;

	for (int n : test_copy) {
		std::println("{}", n);
	}


	return 0;
}