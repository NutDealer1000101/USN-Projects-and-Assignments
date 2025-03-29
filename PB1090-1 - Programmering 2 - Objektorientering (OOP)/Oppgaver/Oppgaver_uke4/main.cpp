import std;

void Oppg6_3() {
	size_t arraySize;
	std::print("Enter array size: ");
	std::cin >> arraySize;

	float* pArray{ new float[arraySize] };

	for (size_t n{ 0 }; n < arraySize; n++) {
		*(pArray + n) = 1.0f / ((n + 1.0f) * 2.0f);
	}

	//for (size_t i{ 0 }; i < arraySize; i++) {
	//	std::println("{}: {:.2}", i, pArray[i]);
	//}

	float sum{ 0.0f };
	for (size_t i{ 0 }; i < arraySize; i++) {
		sum += pArray[i];
	}
	sum = std::sqrt(sum * 6.0f);

	std::println("sqrt(sum * 6): {:.5}", sum);

	delete[] pArray;
	pArray = nullptr;
}

void Oppg6_4() {
	size_t size;
	std::print("Enter array size: ");
	std::cin >> size;

	std::vector<float> values;
	values.reserve(size);

	for (size_t n{ 0 }; n < size; n++) {
		values.push_back(1.0f / ((n + 1.0f) * 2.0f));
	}

	float sum{ 0.0f };
	for (float f : values) {
		sum += f;
	}
	sum = sqrt(sum * 6);

	std::println("sqrt(sum * 6): {:.5}", sum);
}

void Oppg6_5() {
	size_t size;
	std::print("Enter array size: ");
	std::cin >> size;

	auto pArray{ std::make_unique<float[]>(size) };

	for (size_t n{ 0 }; n < size; n++) {
		pArray[n] = 1.0f / ((n + 1.0f) * 2.0f);
	}

	float sum{ 0.0f };
	for (size_t n{ 0 }; n < size; n++) {
		sum += pArray[n];
	}

	sum = sqrt(sum * 6);

	std::println("sqrt(sum * 6): {:.5}", sum);
}

void Oppg6_6() {
	Oppg6_5();
}

void Oppg7_1() {
	std::vector<std::string> names;
	std::vector<float> grades;

	while (true) {
		char response;
		std::print("Add new student and grade? y/n: ");
		std::cin >> response;

		if (response == 'y') {
			std::string name;
			std::print("Enter student name: ");
			std::cin >> name;

			float grade;
			std::print("Enter {}\'s grade: ", name);
			std::cin >> grade;

			names.push_back(name);
			grades.push_back(grade);

			std::println("Added student {} with grade {}.", name, grade);
		}
		else if (response == 'n') {
			break;
		}
		else {
			std::println("Invalid response \'{}\'", response);
		}
	}

	float sum{ 0 };
	for (float f : grades) {
		sum += f;
	}
	float avg{ sum / (float)grades.size() };

	std::println("Average grade: {:.2}", avg);

	int row{ 0 };
	for (size_t i{ 0 }; i < names.size(); i++) {
		std::print("{}: {:.2}\t", names[i], grades[i]);
		
		row++;
		if (row >= 3) {
			row = 0;
			std::println("");
		}
	}
}

void Oppg7_2() {

}


int main() {
	//Oppg6_3();
	//Oppg6_4();
	//Oppg6_5();
	//Oppg6_6();
	Oppg7_1();
	//Oppg7_2();
}