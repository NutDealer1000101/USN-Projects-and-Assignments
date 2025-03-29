import std;

void Oppgave2_1() {
    std::println("\nOppgave 2.1");

    std::println("char: {}", sizeof(char));
    std::println("unsigned char: {}", sizeof(unsigned char));
    std::println("short: {}", sizeof(short));
    std::println("unsigned short: {}", sizeof(unsigned short));
    std::println("int: {}", sizeof(int));
    std::println("unsigned int: {}", sizeof(unsigned int));
    std::println("long: {}", sizeof(long));
    std::println("unsigned long: {}", sizeof(unsigned long));
    std::println("long long: {}", sizeof(long long));
    std::println("unsigned long long: {}", sizeof(unsigned long long));
    std::println("size_t: {}", sizeof(size_t));
    
    std::println("");

    std::println("float: {}", sizeof(float));
    std::println("double: {}", sizeof(double));
    std::println("long double: {}", sizeof(long double));
}

void Oppgave2_4() {
    std::println("\nOppgave 2.4");

    std::print("Height (inches): ");
    float height;
    std::cin >> height;

    std::print("Distance (feet): ");
    float dist_feet;
    std::cin >> dist_feet;

    std::print("Distance (inches): ");
    float dist_inch;
    std::cin >> dist_inch;

    float dist{ 12.0f * dist_feet + dist_inch };

    std::print("Angle (degrees): ");
    float angle;
    std::cin >> angle;

    float height_tree = height + dist * tan(angle);

    std::println("The tree is {:.2f} feet tall.", height_tree);
}

void Oppgave2_5() {
    std::println("\nOppgave 2.5");

    std::print("Weight (pounds): ");
    float weight;
    std::cin >> weight;

    std::print("Height (feet): ");
    float height_feet;
    std::cin >> height_feet;

    std::print("Height (inches): ");
    float height_inch;
    std::cin >> height_inch;

    float height_m{ (12 * height_feet + height_inch) * 0.3048f };
    float weight_kg{ 2.2f * weight };

    float BMI{ weight_kg / sqrt(weight_kg) };

    std::println("Your BMI: {:.2f}", BMI);
}

void Oppgave3_3() {
    std::println("\nOppgave 3.3");
}

enum class Color : unsigned int {
    Red = 0xff0000,
    Green = 0x00ff00,
    Blue = 0x0000ff,
    Yellow = 0xffff00,
    Purple = 0xff00ff,
    Black = 0x000000,
    White = 0xffffff
};

std::string GetRGBComponentsString(Color c) {
    unsigned char R{static_cast<unsigned char>((static_cast<unsigned int>(c) & 0xff0000) >> 16)};
    unsigned char G{static_cast<unsigned char>((static_cast<unsigned int>(c) & 0x00ff00) >> 8)};
    unsigned char B{static_cast<unsigned char>((static_cast<unsigned int>(c) & 0x0000ff))};
    
    return "R: " + std::to_string(R) + " G: " + std::to_string(G) + " B: " + std::to_string(B);
}

void Oppgave3_5() {
    std::println("\nOppgave 3.5");

    Color yellow{ Color::Yellow };
    Color purple{ Color::Purple };
    Color green{ Color::Green };

    std::println("yellow: {}" , GetRGBComponentsString(yellow));

    std::println("purple: {}", GetRGBComponentsString(purple));

    std::println("green: {}", GetRGBComponentsString(green));
}

int main()
{
    //Oppgave2_1();
    //Oppgave2_4();
    //Oppgave2_5();
    //Oppgave3_3();
    //Oppgave3_5();

    return 0;
}