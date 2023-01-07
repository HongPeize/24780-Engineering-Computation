#pragma once
#pragma warning(disable:4996)

#include <string>
#include <vector>

//#include <msclr\marshal_cppstd.h>  //  needed for string conversions from CLI

using namespace std;

class StringPlus {
public:
	// remove leading spaces
	static string ltrim(const string& inString) {
		auto firstNonSpace = inString.find_first_not_of(" ");
		if (firstNonSpace == -1)
			return "";
		else
			return inString.substr(firstNonSpace);
	}

	// remove trailing spaces
	static string rtrim(const string& inString) {
		return inString.substr(0, inString.find_last_not_of(" ") + 1);
	}

	// remove both leading and trailing spaces
	static string trim(const string& inString) {
		return ltrim(rtrim(inString));
	}

	// change all letters of a string to capital letters
	static string upperCase(const string& inString);

	// change all letters of a string to lowercase letters
	static string lowerCase(const string& inString);

	// change first letter of each word to capital and all other letters to lowercase
	static string properCase(const string& inString);

	//static string convertString(System::String^ aString) { // needed for CLI
	//	msclr::interop::marshal_context context;
	//	std::string standardString = context.marshal_as<std::string>(aString);
	//	return standardString;
	//}

	// takes a string and splits it into a vector of strings using the delimiter 
	static std::vector<std::string> split(std::string str, std::string delim);

	// adds newline characters to a string to break it up at spaces into shorter lines
	// (will not break up words)
	static string wrapLongLine(const string& outString, int lineLength);

	// replaces all instances of "from" in "original" to "to"
	static string replaceAll(const string& original, 
		const string& from, const string& to);

	// prints a number with given significant figures (rounding and adding zeros as needed)
	static string sigFig(double theValue, int figCount);

	// robust method of getting a number from console
	static double getDouble(std::istream& inputStream, const std::string& prompt);

};