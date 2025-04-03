/*
*	A stream is used to send a sequence of characters or numbers in and out of a program.
*	Elements sent into/out of a stream are put into a buffer until they're
*	sent to where they're accually going, called flushing the buffer.
*	Two common cases of streams in C++ are:
*		- std::cout and std::cin for input/output from terminal.
*		- std::ifstream and std::ofstream for input/output from files.
*/

import std;

void cin_demo() {
	int i;
	std::cout << "Enter an integer: ";

	// If something goes wrong when reading from an istream, one of 4 error flags will be set:
	//	ios::eofbit:	End of file is reached
	//	ios::failbit:	Something went wrong, but the stream itself is still OK
	//	ios::badbit:	The stream might be fucked
	//	ios::goodbit:	Set if none of the other flags are set
	//
	//	To clear the flags, use clear()
	std::cin >> i;
	while (!std::cin) {
		// Something went wrong, clean up stream and ask again

		std::cin.clear();	// Clear flags
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Erase other characters left in the buffer
		std::cout << "Something went wrong, try again: ";
		std::cin >> i;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	double d;
	std::cout << "Enter a double: ";
	std::cin >> d;
	while (!std::cin) {
		std::cin.clear();	// Clear flags
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Erase other characters left in the buffer
		std::cout << "Something went wrong, try again: ";
		std::cin >> d;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::string s;
	std::cout << "Finally, enter a string: ";
	std::cin >> s;
	while (!std::cin) {
		std::cin.clear();	// Clear flags
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Erase other characters left in the buffer
		std::cout << "Something went wrong, try again: ";
		std::cin >> s;
	}

	std::cout << "You entered: " << i << ", " << d << ", " << s << std::endl;
}

void ifstream_demo() {
	std::string filename = "text.txt";
	std::ifstream file;
	file.open(filename, std::ios::in);	// Loads the file (if it exists) and signals to the OS that this file is now in use
										// Can also be done in the constructor for same effect
	if (!file) {
		std::cout << "Could not find file \"" << filename << "\"" << std::endl;
		return;
	}

	std::cout << "Printing contents of " << filename << ":" << std::endl;
	for (std::string line; std::getline(file, line);) {
		std::cout << line << std::endl;
	}

	file.close();	// Signals to the OS that the file is no longer in use and closes the file
					// Will also be called in the destructor, so no worries about any problems there
}

void ofstream_demo() {
	std::string filename = "log.txt";
	std::ofstream file;
	file.open(filename, std::ios::out);		// std::ios::app would append to the end of the file instead of overwriting it
	if (!file) {
		std::cout << "Could not create file \"" << filename << "\"" << std::endl;
		return;
	}

	std::cout << "Enter some strings to log to \"" << filename << "\"" << std::endl;
	std::cout << "Enter \"done\" to exit." << std::endl;
	
	std::string line = "";
	while (true) {
		std::getline(std::cin, line);	// Gets a line from a stream until a delimiter (default '\n')
		if (line == "done") break;

		file << line << "\n";
	}

	std::cout << "Done writing to file!" << std::endl;
}

int main() {
	//cin_demo();
	std::cout << std::endl;
	ifstream_demo();
	std::cout << std::endl;
	ofstream_demo();
	return 0;
}