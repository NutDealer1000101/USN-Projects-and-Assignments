import std;

// Forward declarations
int DoubleOf(int n);
int Fib(int n);
void PrintArray(int arr[], size_t size, bool linebreak = false);
int* PointerToLargest(int a, int b);

int main(int argc, char* argv[]) {
	// Arguments given to main()
	std::println("Arguments to main():");
	for (int i = 0; i < argc; i++) {
		std::println("arg {}:\t{}", i, argv[i]);
	}
	
	int n;
	std::print("Enter number: ");
	std::cin >> n;
	
	std::println("{} times 2 is {}", n, DoubleOf(n));
	std::println("Fibonacci number {} is {}", n, Fib(n));

	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		arr[i] = i;
	}

	PrintArray(arr, n, true);

	delete[] arr;
	arr = nullptr;

	int* p = PointerToLargest(2, 4);
	std::cout << *p << std::endl;	// Will print 4 (yay)
	std::println("{}", *p);			// Will print garbage (overwrites the data on the stack)
}

// Regular ah function
int DoubleOf(int n) {
	return 2 * n;
}

// Recursion
int Fib(int n) {
	if (n <= 1) return 1;
	return Fib(n - 2) + Fib(n - 1);
}

// Arrays as arguments
void PrintArray(int arr[], size_t size, bool linebreak) {
	std::print("{{");
	for (int i = 0; i < size; i++) {
		std::print("{}", arr[i]);
		if (i < size - 1) std::print(", ");
	}
	std::print("}}");
	if (linebreak) std::println("");
}

// Returning pointer to stack-allocated variable
// DON'T DO THIS, PLEASE
int* PointerToLargest(int a, int b) {
	return a > b ? &a : &b;
}