import std;

class Fraction {
public:
	Fraction(int numerator, int denominator) 
		:
		numerator(numerator),
		denominator(denominator)
	{
		//	+ / +  ->  + / +	ignore
		//	- / +  ->  - / +	ignore
		//	+ / -  ->  - / +	flip signs
		//	- / -  ->  + / +	flip signs
		if ((numerator < 0 && denominator < 0) || (numerator > 0 && denominator < 0)) {
			numerator = -numerator;
			denominator = -denominator;
		}

		Simplify();
	}

	void Simplify() {
		// Checking all numbers bewteen (1, denominator] in descending order
		for (int n = Denominator(); n > 1; n--) {
			// If both are divisible by the number
			// , simplify
			if (Denominator() % n == 0 && Numerator() % n == 0) {
				numerator /= n;
				denominator /= n;
			}
		}
		// If none match, it's already simplified
	}

	// Operators
	Fraction operator*(const Fraction& rhs) const {
		int num = numerator * rhs.Numerator();
		int den = denominator * rhs.Denominator();

		return Fraction(num, den);
	}

	Fraction operator+(const Fraction& rhs) const {
		//	a/b + c/d
		//	a/b + (c*(b/d)) / (d*(b/d))
		//	a/b	+ (c*(b/d)) / b
		//	(a + c * b/d) / b
		//	(a * d + c * b) / b * d

		int num = Numerator() * rhs.Denominator() + rhs.Numerator() * Denominator();
		int den = Denominator() * rhs.Denominator();

		return Fraction(num, den);
	}

	bool operator<(const Fraction& rhs) const {
		return Value() < rhs.Value();
	}

	// Getters
	int Numerator() const {
		return numerator;
	}
	int Denominator() const {
		return denominator;
	}
	float Value() const {
		return (float)Numerator() / (float)Denominator();
	}
private:
	int numerator;
	int denominator;
};

// Overloading stream operator
std::ostream& operator<<(std::ostream& ost, const Fraction& frac) {
	return ost << frac.Numerator() << "/" << frac.Denominator();
}

int main() {
	Fraction f1{ 5, 2 };
	Fraction f2{ 2, 3 };
	std::cout << "f1: " << f1 << "\nf2: " << f2 << std::endl;

	Fraction f3 = f1 * f2;
	std::cout << "f1 * f2 -> " << f3 << std::endl;

	Fraction f4 = f1 + f2;
	std::cout << "f1 + f2 -> " << f4 << std::endl;

	return 0;
}