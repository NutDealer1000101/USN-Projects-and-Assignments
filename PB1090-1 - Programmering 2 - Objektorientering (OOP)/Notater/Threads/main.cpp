import std;

void MyFunc1(std::mutex& cout_lock) {
	for (std::size_t i = 0; i < 100; i++) {
		cout_lock.lock();
		std::println("{} I'm a thread!", i);
		cout_lock.unlock();
	}
}

void MyFunc2(std::mutex& cout_lock, std::size_t id) {
	for (std::size_t i = 0; i < 100; i++) {
		cout_lock.lock();
		std::println("{} I'm thread number {}", i, id);
		cout_lock.unlock();
	}
}

bool IsPrime(std::size_t n) {
	std::println("Calculating, please wait...");
	for (std::size_t i = 2; i < n; ++i) {
		if (n % i == 0) return false;
	}
	return true;
}

int main() {
	// Threads
	std::mutex cout_lock;	// Mutex to make sure only one thread uses cout at once

	std::thread t1{ MyFunc1, std::ref(cout_lock) };
	std::thread t2{ MyFunc2, std::ref(cout_lock), 2 };

	for (std::size_t i = 0; i < 100; i++) {
		cout_lock.lock();	// Lock other threads from "claiming" the same mutex
		std::println("{} I'm main!", i);
		cout_lock.unlock();	// Now, other threads can "claim" the mutex again
	}

	t1.join();	// Main will wait until t1 is finished
	t2.join();	// Same here with t2


	// Asyncronous function calls
	std::size_t n = 5'915'587'277;
	std::future<bool> fut = std::async( IsPrime, n );
	std::println("Checking if {} is a prime number...", n);

	// Other stuff can happen here while IsPrime is being calculated!

	bool result = fut.get();	// Will block execution until the result is ready

	if (result) {
		std::println("{} is a prime number!", n);
	}
	else {
		std::println("{} is not a prime number!", n);
	}

	return 0;
} 