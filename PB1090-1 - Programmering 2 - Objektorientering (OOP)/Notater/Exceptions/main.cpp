import std;
import nutex;

int main()
{
    while (true) {
        try {
            int num;
            int den;
            std::print("Enter numerator: ");
            std::cin >> num;
            std::print("Enter denominator: ");
            std::cin >> den;

            if (num == 0 && den == 0) throw nut::LogicError("What?");

            if (den == 0) throw nut::DivisonByZero();

            std::println("{} / {} = {}", num, den, num / den);
        }
        catch (const nut::DivisonByZero& e) {
            std::println("DivsionByZero: {}", e.what());
        }
        catch (const nut::LogicError& e) {
            std::println("LogicError: {}", e.what());
        }
        catch (...) {
            std::println("Unknown: Something went wrong.");
        }
    }
}