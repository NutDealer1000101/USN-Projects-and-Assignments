import std;

int main()
{
	std::string str{ "Hei alle sammen" };

	std::println("Size of str: {}", str.length());

	// Substrings
	std::string substr{ str, 2, 12 };
	std::println("\"{}\" is a substring of \"{}\"", substr, str);
	std::string substr2{ str.substr(5, 6) };	// 6 characters from index 5
	std::println("\"{}\" is also a substring of \"{}\"", substr2, str);

	// Concatenating strings
	std::string str2{ str + substr + "!!"};
	std::println("What the... \"{}\"", str2);

	// Appending values
	str2.append("waz gud fam?");
	str2 += "gucci flip flops";
	str += '2';
	std::println("\"{}\"", str2); 

	// ... to string
	int val{ 69 };
	long val2{ 123456789L };

	std::string str3{ std::to_string(val) + " " + std::to_string(val2) };
	std::println("{}", str3);

	// Reading input to string
	std::string str4;
	/*
	std::cin >> str4; // Reads until a space
	std::println("{}", str4); // Hello world -> Hello
	*/

	/*
	std::getline(std::cin, str4); // Reads a whole line (until line break)
	// std::getline(std::cin, str4, <delimiter>);
	std::println("{}", str4);	// Hello world -> Hello world
	*/

	// Comparing strings
	std::string str5{ "My Haeurgup jelly" };
	std::string str6{ "More of the same, really..." };

	if (str5 < str6) {
		std::println("str5 is less than str6");
	}
	else {
		std::println("str5 is greater than str6");
	}

	std::println("{}", str5.compare(str6));
	// -1 -> str5 < str6
	// 0  -> str5 == str6
	// 1  -> str5 > str6

	if (str5.starts_with("My")) {	// .ends_with() also exists!
		std::println("Ye");
	}
	else {
		std::println("Nah");
	}

	// Searching strings
	std::println("{}", str6.find("same"));
	std::println("{}", str6.find("Ohio"));	// returns std::string::npos
}
