/*
*   Oblig 2 - Lukas Andersen 272914
*   Hver oppgave ligger i sin egen funksjon med samme navn
*/
import std;
#include <assert.h>

namespace la
{
    std::optional<int> find_minimum(const std::vector<int>& data) {
        if (data.empty())
            return std::nullopt;

        // Optimering for å finne minste verdi
        int min{ data.at(0) };
        for (int n : data) {
            if (n < min)
                min = n;
        }

        return min;
    }

    void Oppgave1() {

        // Noen tester for å sjekke at funksjonen fungerer som den skal

        std::vector<int> vec1{ 4, 2, 10 };
        assert(find_minimum(vec1).has_value() && find_minimum(vec1).value() == 2);

        std::vector<int> vec2{ -10, 50, 10 };
        assert(find_minimum(vec2).has_value() && find_minimum(vec2).value() == -10);

        std::vector<int> vec3{ 4 };
        assert(find_minimum(vec3).has_value() && find_minimum(vec3).value() == 4);

        std::vector<int> vec4{};
        assert(!find_minimum(vec4).has_value());
    }

    // Er også mulig å bruke template<> her
    auto sum(const auto& a, const auto& b) {
        return a + b;
    }

    // Spesialiserer seg på peker-typer
    auto sum(auto* pa, auto* pb) {
        return *pa + *pb;
    }

    void Oppgave2() {
        // Noen tester for å sjekke at funksjonen fungerer som den skal
        
        int a{ 5 };
        long b{ 7L };
        float c{ 12.5f };

        int& refa = a;
        float& refc = c;

        assert(sum(a, 3) == 8);
        assert(sum(a, b) == 12L);
        assert(sum(b, c) == 19.5f);
        assert(sum(refa, refc) == 17.5f);

        // Sjekker også med pekere
        assert(sum(&a, &c) == 17.5f);
    }

    template<typename T>
    std::size_t CountOccurences(std::span<T> data, T value) {
        size_t count{ 0 };

        // Teller elementer
        for (const T& n : data) {
            if (n == value)
                count++;
        }

        return count;
    }

    void Oppgave3() {
        // Noen tester for å sjekke at funksjonen fungerer som den skal
        
        int arr1[]{ 34, 2, 123, 2, 6, 7, 3, 22, 55, 2, 2, 19, 2, 12 }; // 5stk 2 totalt
        assert(CountOccurences<int>(arr1, 2) == 5);

        std::vector<double> vec1{ 21.0, 15.0, 69.5, 192.2, 15.0, 42.42, 15.0 }; // 3stk 15.0 totalt
        assert(CountOccurences<double>(vec1, 15.0) == 3);

        std::vector<int> vec2{ 3, 2, 6, 4, 9, 4, 2, 3, 2, 2, 4, 6 }; // 0stk 1 totalt
        assert(CountOccurences<int>(vec2, 1) == 0);
    }
}

int main(int, char**) {
    using namespace la;

    Oppgave1();
    Oppgave2();
    Oppgave3();

    return 0;
}