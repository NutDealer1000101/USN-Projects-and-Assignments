import std;

long FindMax(const long* arr, std::size_t size) {
	if (size == 0) return 0;

	long max{ arr[0] };
	for (std::size_t i{ 0 }; i < size; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}

	return max;
}
long FindMin(const long* arr, std::size_t size) {
	if (size == 0) return 0;

	long min{ arr[0] };
	for (std::size_t i{ 0 }; i < size; i++) {
		if (arr[i] < min) {
			min = arr[i];
		}
	}

	return min;
}


template<typename T, typename Comparison>
T FindOptimum(const T* data, std::size_t size, Comparison cmp) {
	T opt{ data[0] };

	for (std::size_t i{ 0 }; i < size; i++) {
		if (cmp(data[i], opt)) {
			opt = data[i];
		}
	}

	return opt;
}

template<typename T>
bool Less(const T& a, const T& b) {
	return a < b;
}

template<typename T>
bool Greater(const T& a, const T& b) {
	return a > b;
}

template<typename T>
class C_less {
public:
	C_less() {
		std::println("Eyyy, I'm a fuckin' function object of type C_less!");
	}

	bool operator()(const T& a, const T& b) { return a < b; };
};

template<typename T>
class C_greater {
public:
	C_greater() {
		std::println("Eyyy, I'm a fuckin' function object of type C_greater!");
	}

	bool operator()(const T& a, const T& b) const { return a > b; };
};

template<typename T>
class Nearest {
public:
	Nearest(const T& goal)
		:
		goal(goal) 
	{}

	bool operator()(const T& x, const T& y) const {
		return std::abs(goal - x) < std::abs(goal - y);
	}
private:
	T goal;
};

int main() {
	// Function pointer syntax:
	// <return_type> (*<pointer_name>)(<parameter_list>) {<function_name>}

	long (*p_fun)(const long* arr, std::size_t size) { FindMax };
	//auto p_fun{ FindMax };

	long data[]{ 10L, -55L, 21L, -25L, 42L, 42L, 100L, -69L, 50L};

	std::println("1st attempt - Function pointers:\nMax value: {}", p_fun(data, std::size(data)));
	p_fun = FindMin;
	std::println("Min value: {}", p_fun(data, std::size(data)));

	std::println("\n2nd attempt - Function pointers as parameter:\nMax value: {}\nMin value: {}", 
				 FindOptimum(data, std::size(data), Greater<long>),
				 FindOptimum(data, std::size(data), Less<long>));

	std::println("\n3rd attempt - Lambda expressions:\nMax value: {}\nMin value: {}",
				 FindOptimum(data, std::size(data), [](const long& a, const long& b)->bool { return a > b; }),
				 FindOptimum(data, std::size(data), [](const long& a, const long& b)->bool { return a < b; }));

	auto lambda_greater{ [](const long& a, const long& b)->bool { return a > b; } };
	auto lambda_less{ [](const long& a, const long& b)->bool { return a < b; } };

	std::println("\n4th attempt - Named lambdas:\nMax value: {}\nMin value: {}",
				 FindOptimum(data, std::size(data), lambda_greater),
				 FindOptimum(data, std::size(data), lambda_less));

	std::println("\n5th attempt - Function objects:\nMax value: {}\nMin value: {}",
				 FindOptimum(data, std::size(data), C_greater<long>{}),
				 FindOptimum(data, std::size(data), C_less<long>{}));

	std::println("\n6th attempt - STL function objects:\nMax value: {}\nMin value: {}",
				 FindOptimum(data, std::size(data), std::greater<long>{}),
				 FindOptimum(data, std::size(data), std::less<long>{}));

	std::println("\nValue nearest 70: {}", FindOptimum(data, std::size(data), Nearest<long>{70}));
	std::println("\nValue nearest 25: {}", FindOptimum(data, std::size(data), Nearest<long>{25}));

	return 0;
}