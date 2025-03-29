import std;

std::string GetReversedString(const std::string& s) {
	std::string reversed = s;

	for (std::size_t i_start{ 0 }, i_end{ s.size() - 1 }; i_start < s.size(); i_start++, i_end--) {
		reversed.at(i_start) = s.at(i_end);
	}

	return reversed;
}

void Oppg8_2() {
	std::string input;
	std::print("Enter some text: ");
	std::cin >> input;

	std::println("Reversed text: \"{}\"", GetReversedString(input));
}

int Plus(int a, int b) {
	return a + b;
}

double Plus(double a, double b) {
	return a + b;
}

std::string Plus(const std::string& a, const std::string& b) {
	return a + b;
}

void Oppg8_4() {
	const int n{ Plus(3, 4) };
	const double d{ Plus(3.2, 4.2) };
	const std::string s{ Plus("he", "llo") };
	const std::string s1{ "aaa" };
	const std::string s2{ "bbb" };
	const std::string s3{ Plus(s1, s2) };
}

bool IsPrime(unsigned int n) {
	if (n <= 1) return false;

	for (unsigned int i{ 2 }; i < n; i++) {
		if (n % i == 0) return false;
	}
	return true;
}

std::vector<unsigned int> CreateIntegerVector(unsigned int max, unsigned int min = 1) {
	std::vector<unsigned int> values;
	values.reserve(max - min);

	for (unsigned int i = min; i < max; i++) {
		values.push_back(i);
	}

	return values;
}

std::vector<unsigned int> PrimesFromVector(const std::vector<unsigned int>& values) {
	std::vector<unsigned int> primes;

	for (unsigned int n : values) {
		if (IsPrime(n)) primes.push_back(n);
	}

	return primes;
}

void Oppg8_5() {
	unsigned int n;
	std::print("Enter number: ");
	std::cin >> n;

	std::vector<unsigned int> primes = std::move(PrimesFromVector(CreateIntegerVector(n + 1)));

	std::println("All primes less than or equal to {}:\n{}", n, primes);
}

std::vector<int> FiveLargest(const std::vector<int>& data) {
	std::vector<int> values;
	values.reserve(5);

	std::size_t begin = data.size() - std::min(data.size(), (std::size_t)5);
	std::size_t end = data.size();

	for (; begin < end; begin++) {
		values.push_back(data.at(begin));
	}

	return values;
}

std::vector<int> FiveSmallest(const std::vector<int>& data) {
	std::vector<int> values;
	values.reserve(5);

	std::size_t begin = 0;
	std::size_t end = std::min(data.size(), (std::size_t)5);

	for (; begin < end; begin++) {
		values.push_back(data.at(begin));
	}

	return values;
}

void Oppg8_6() {
	std::vector<int> grades;

	while (true) {
		int n;
		std::print("Enter a grade (0 - 100), or a negative number to print info: ");
		std::cin >> n;

		if (n >= 0 && n <= 100) {
			// Add shit
			std::println("Adding {} to grade list.", n);
			grades.push_back(n);
		}
		else if (n < 0) {
			if (grades.size() == 0) {
				std::println("Add some grades first.");
				continue;
			}
			// Print shit
			std::sort(grades.begin(), grades.end());

			std::println("The five largest grades: {}", FiveLargest(grades));
			std::println("The five lowest grades: {}", FiveSmallest(grades));

			break;
		}
		else {
			// You're shit
			std::println("Input must be between 0 and 100 (inclusive), or a negative number.");
		}
	}
}

void Oppg8_7() {
}

int main() {
	//Oppg8_2();
	//Oppg8_4();
	//Oppg8_5();
	Oppg8_6();
	//Oppg8_7();
	return 0;
}