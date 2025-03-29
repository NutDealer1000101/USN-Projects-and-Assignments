import std;

#include <assert.h>

/*
*	Vocabulary Types:
*	Datatypes given by the standard library
*	Some are already known:
*	Vector
*	Array
*	Smart Pointers
*/

std::optional<char> CharacterAt(const std::string& str, std::size_t index) {
	if (index >= str.size()) {
		// If index out of bounds, return "empty value"
		return std::nullopt;
	}
	else {
		// Returning regular value
		return str.at(index);
	}
}

std::optional<std::size_t> FindLast(const std::string& s, char charToFind, std::optional<std::size_t> startIndex = std::nullopt) {
	// What could go wrong?
	//		String could be empty
	//		Start index is out of bounds (<0 or >=s.size())
	
	// If string is empty, dont even bother checking
	if (s.empty()) return std::nullopt;

	// Start index is too large
	if (startIndex.has_value() && startIndex.value() >= s.size()) return std::nullopt;
	
	// If the start index is empty, it gets set to the last element instead
	std::size_t index{ startIndex.value_or(s.size() - 1) };
	while (true) {
		// The character was found
		if (s.at(index) == charToFind) return s.at(index);

		// Start of string and no character was found
		if (index == 0) return std::nullopt;

		index--;
	}
}

int CountOccurences(std::string_view str_view, char charToCount) {
	int count{ 0 };

	for (char c : str_view) {
		if (c == charToCount) count++;
	}

	return count;
}

double FindLargest(std::span<const double> data) {
	double largest{data[0]};

	for (double n : data) {
		if (n > largest) largest = n;
	}

	return largest;
}

void Multiply(std::span<double> data, double multiplier) {
	for (double& d : data) {
		d *= multiplier;
	}
}

int main() {
	// Optional: May hold a value, or be empty. 
	// Comes with methods to check value and state.
	// Good to return from a function that may return nothing.

	const std::string str{ "Amogus" };

	// This should be valid, no empty value gets returned
	std::optional<char> val{ CharacterAt(str, 2) };
	assert(val.has_value());
	assert(val.value() == 'o');

	// Index is out of bounds, val should not contain a value
	val = CharacterAt(str, 10);
	assert(!val.has_value());

	assert(!FindLast("Amongus", 'z', 20).has_value());
	assert(FindLast("Amongus", 'g').has_value());



	// String view: pass around strings without ever copying the text. However, the string cannot be modified.
	// Why not just use const std::string&? String literals and char* will be copied anyways! 
	// std::string_view solves this case.
	
	std::string str2{"Holy moley maccaroni!"};
	int count{ CountOccurences(str2, 'o') };	// This works the same as const std::string&, nothing special.

	count = CountOccurences("Jeez Louize!", 'e'); // This also works the same, but the literal never gets copied!



	// Spans: Create one function to go through different kinds of containers
	// std::span<T> work with most STL-containers and even regular arrays.

	std::vector<double> data_stdvector = { 0.0, 1.0, 10.5, 4.2 };
	std::array<double, 4> data_stdarray = { 0.0, 1.0, 10.5, 4.2 };
	double data_array[] = { 0.0, 1.0, 10.5, 4.2 };

	// One function to rule them all!
	// The containers just have to be converted to a span
	double max1 = FindLargest(std::span<double>(data_stdvector));
	double max2 = FindLargest(std::span<double>(data_stdarray));

	// When passing regular arrays, the size must also be passed, unless the compiler already know the size of the array.
	// This should work without the size in this case, but if we just have a pointer the size must be passed.
	double max3 = FindLargest(std::span<double>(data_array, std::size(data_array)));	

	assert(max1 == max2 && max2 == max3);

	// If the span refers to constant data, or the data doesn't need to be modified, we use std::span<const T>
	// Else, we just use std::span<T>

	//This function, for example, multiplies all elements with a number and needs to be std::span<T>
	Multiply(std::span<double>(data_stdvector), 3.5);
	Multiply(std::span<double>(data_stdarray), 3.5);
	Multiply(std::span<double>(data_array, std::size(data_array)), 3.5);



	std::println("Nothing went wrong, great work :)");
	return 0;
}