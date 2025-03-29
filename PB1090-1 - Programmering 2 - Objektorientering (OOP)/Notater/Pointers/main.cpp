import std;

int main()
{
	/*
	// Regular pointers
	int value = 69;
	const int const_value = 420;

	int* pValue1 = &value;							//Pointer to an int
	int* const pValue2 = &value;					//Const pointer to an int (pointer can't change adress)
	const int* pConst_value1 = &const_value;		//Pointer to a const int
	const int* const pConst_value2 = &const_value;	//Const pointer to a const int (pointer can't change adress)

	// <constness of variable> <type of variable>* <constness of pointer> <pointer name>
	
	*/

	//Unique pointer
	auto pValue = std::make_unique<int>(69);	// Allocates 69 on the heap
	pValue = std::make_unique<int>(420);		// Allocates 420 on the heap, the old adress (69) is deleted
	pValue.reset();								// Ownership released, 420 is deleted aswell

	//Shared pointer and weak pointer
	auto pShared1 = std::make_shared<int>(69);	// Allocates 69 on the heap, 1 strong ref
	auto pShared2 = pShared1;					// 2 strong refs
	auto pShared3 = pShared2;					// 3 strong refs

	auto pRaw = pShared3.get();					// Big yikes, holds pointer but no references made
	std::weak_ptr<int> pWeak = pShared1;		// 3 strong refs, 1 weak ref

												// pWeak must be converted to another shared pointer before accessing	
	if (auto pShared4 = pWeak.lock()) {			// This creates another strong reference, 4 strong refs, 1 weak ref
		// If-test passed, we gucci (memory is valid)
	}
	else {
		// If-test failed, the memory is expired and can't be used
	}
	bool expired = pWeak.expired();				// false, the memory is still active

	pShared1.reset();							// 2 strong refs, 1 weak ref
	pShared3.reset();							// 1 strong ref, 1 weak ref
	pShared2.reset();							// 0 strong refs, the memory is deleted. still 1 weak ref

	expired = pWeak.expired();					// true, the memory is deleted
												// Note: the raw pointer is clueless
	

	auto p_shared = std::make_shared<int>(69);
	std::weak_ptr<int> p_weak = p_shared;

	if (auto p_shared2 = p_weak.lock()) {
		std::println("*p_weak: {}", *p_shared2);
	}
	else {
		std::println("p_shared is expired.");
	}

	p_shared.reset();

	if (auto p_shared2 = p_weak.lock()) {
		std::println("*p_weak: {}", *p_shared2);
	}
	else {
		std::println("p_shared is expired.");
	}
}