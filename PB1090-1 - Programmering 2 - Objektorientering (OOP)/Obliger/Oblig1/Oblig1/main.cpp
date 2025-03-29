/*
*   Oblig 1 - Lukas Andersen 272914
*   Hver oppgave ligger i sin egen funksjon med samme navn.
*/

import std;

void Oppgave1() {
    int tall1, tall2;

    std::print("Enter an integer: ");
    std::cin >> tall1;
    std::print("Enter another integer: ");
    std::cin >> tall2;

    auto ordering = tall1 <=> tall2;

    /*
    Hvis tall1 > tall2, byttes verdiene i variablene. Da kommer tall1 til å alltid inneholde den minste verdien.
    I stedet for std::swap() kunne også denne løsningen blitt brukt:
        int temp = tall1;
        tall1 = tall2;
        tall2 = temp;
    */
    if (ordering == std::strong_ordering::greater) std::swap(tall1, tall2);

    std::println("Smallest value:\t{0} -> 0b{0:b}", tall1);
    std::println("Largest value:\t{0} -> 0x{0:X}", tall2);
}

void Oppgave2() {
    std::vector<int> tall;
    while (true) {
        int input;
        std::print("Enter integer to add it, or '0' to print contents and exit: ");
        std::cin >> input;

        if (input == 0) {
            std::println("Printing contents...");
            for (int i : tall) {
                std::println("{}", i);
            }
            std::println("Done!");
            break;
        }
        else {
            std::println("Adding {} to vector...", input);
            tall.push_back(input);
        }
    }
}

void set_value_in_position(unsigned short& data, size_t position, bool value) {
    if (value == 0) {
        // Verdien skal settes til 0, og gjøres ved å AND-e dette bitet med 0. De andre bitene må AND-es med 1
        // Masken vil se omtrent slik ut:    ...1111101111...
        data &= ~(1 << position);
    }
    else {
        // Verdien skal settes til 1, og gjøres ved å OR-e dette bitet med 1. Hva de andre bitene blir OR-et med spiller egentlig ingen rolle.
        // Masken vil se omtrent slik ut:    ...0000010000...
        data |= 1 << position;
    }
}

bool get_value_in_position(unsigned short data, size_t position) {
    return static_cast<bool>((data >> position) & 1);
}

void Oppgave3() {
    // Dataen starter med kun 0'ere
    unsigned short data = 0b0000000000000000;
    
    // Tester å sette noen bits til 1
    set_value_in_position(data, 0, 1);
    set_value_in_position(data, 1, 1);
    set_value_in_position(data, 14, 1);
    set_value_in_position(data, 15, 1);

    // Tester å sette noen bits til 0
    set_value_in_position(data, 1, 0);
    set_value_in_position(data, 15, 0);
    set_value_in_position(data, 2, 0);

    // Tester å hente ut verdier fra dataen
    std::println("Pos 0: {:d}", get_value_in_position(data, 0));     // -> 1
    std::println("Pos 1: {:d}", get_value_in_position(data, 1));     // -> 0
    std::println("Pos 2: {:d}", get_value_in_position(data, 2));     // -> 0
    std::println("Pos 14: {:d}", get_value_in_position(data, 14));   // -> 1
    std::println("Pos 15: {:d}", get_value_in_position(data, 15));   // -> 0
}

int main()
{
    //Oppgave1();
    //Oppgave2();
    Oppgave3();
}
