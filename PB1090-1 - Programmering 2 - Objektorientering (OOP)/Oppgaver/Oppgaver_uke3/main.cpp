import std;

void oppg4_1() {
    int i1;
    std::print("Enter an integer: ");
    std::cin >> i1;

    int i2;
    std::print("Enter another integer: ");
    std::cin >> i2;

    if (i1 == i2) {
        std::println("These integers are the same.");
    }
    else {
        std::println("These integers are not the same.");
    }
}

void oppg4_3() {
    float n;
    std::print("Enter a number between 1 and 100: ");
    std::cin >> n;

    if (n < 1.0f || n > 100.0f) {
        std::println("{} is not between 1 and 100.", n);
    }
    else {
        auto ordering{ n <=> 50.0f };

        if (ordering == std::partial_ordering::less) {
            std::println("{} is less than 50.", n);
        }
        else if (ordering == std::partial_ordering::equivalent) {
            std::println("{} is equivalent to 50.", n);
        }
        else if (ordering == std::partial_ordering::greater) {
            std::println("{} is greater than 50.", n);
        }
        else {
            std::println("Uhhh... {} is unordered.", n);
        }
    }
}

void oppg5_1() {
    unsigned int limit;
    std::print("Enter limit: ");
    std::cin >> limit;

    for (unsigned int i{ 1 }; i <= limit; i++) {
        if (i % 2 == 0) continue;
        
        std::println("{}", i * i);
    }
}

void oppg5_3() {
    char s[200];
    std::print("Write some text, and end the text with '#': ");
    std::cin.getline(s, 200);

    int n_characters{ 0 }, index{ 0 };
    char c;
    do {
        c = s[index++];
        if (!std::isspace(c)) n_characters++;
    } while (c != '\0' && c != '#');

    std::println("Found {} nonwhitespace characters in the string.", n_characters);
}

void oppg5_6() {
    std::vector<int> numbers;
    int upper;
    std::print("Enter upper bound: ");
    std::cin >> upper;

    numbers.reserve(upper);
    for (int i{ 1 }; i <= upper; i++) {
        numbers.push_back(i);
    }

    for (int i{ 0 }, n_output{ 0 }; i < numbers.size(); i++) {
        int n = numbers.at(i);
        if (n % 7 == 0 || n % 13 == 0) continue;
        std::print("{}\t", n);
        
        n_output++;
        if (n_output >= 10) {
            n_output = 0;
            std::println("");
        }
    }
}

void oppg5_8() {
    std::array<size_t, 93> numbers = { 1, 1 };

    for (size_t i = 2; i < numbers.size(); i++) {
        numbers.at(i) = numbers.at(i - 2) + numbers.at(i - 1);
    }

    for (size_t n : numbers) {
        std::println("{}", n);
    }
}

int main() {
    //oppg4_1();
    //oppg4_3();
    //oppg5_1();
    //oppg5_3();
    //oppg5_6();
    oppg5_8();
}