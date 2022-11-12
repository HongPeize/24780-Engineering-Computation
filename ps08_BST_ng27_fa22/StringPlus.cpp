#include <sstream>
#include <iostream>
#include "StringPlus.h"


string StringPlus::upperCase(const string& inString)
{
	string output = "";
	for (int i = 0; i < inString.length(); i++) {
		if ('a' <= inString[i] && inString[i] <= 'z')
			output += inString[i] + ('A' - 'a');
		else
			output += inString[i];
	}
	return output;
}

string StringPlus::lowerCase(const string& inString)
{
	string output = "";
	for (int i = 0; i < inString.length(); i++) {
		if ('A' <= inString[i] && inString[i] <= 'Z')
			output += inString[i] - ('A' - 'a');
		else
			output += inString[i];
	}
	return output;
}

string StringPlus::properCase(const string& inString)
{
	string output = "";
	bool firstLetter = true;
	int i = 0;
	while (i < inString.length()) {
		// advance to first letter, copying along the way
		while (i < inString.length() 
			&& !('A' <= inString[i] && inString[i] <= 'Z')  // not a capital letter
			&& !('a' <= inString[i] && inString[i] <= 'z')) // not a lower-case letter
			output += inString[i++];   // note that using i++ here increments i AFTER using
		
		// capitalize first letter of word if it is lower-case
		if ('a' <= inString[i] && inString[i] <= 'z')
			output += inString[i++] + ('A' - 'a');
		else
			output += inString[i++];

		// advance to next space, shifting any capital letters to lower case along the way
		while (i < inString.length() && inString[i] != ' ') 
			if ('A' <= inString[i] && inString[i] <= 'Z')
				output += inString[i++] - ('A' - 'a');
			else
				output += inString[i++];

		// put space into output
		if (i < inString.length())
			output += inString[i++];
	}
	return output;
}

std::vector<std::string> StringPlus::split(std::string str, std::string delim)
{
	char* cstr = const_cast<char*>(str.c_str());
	char* current;
	std::vector<std::string> result;
	current = strtok(cstr, delim.c_str());
	while (current != NULL) {
		result.push_back(current);
		current = strtok(NULL, delim.c_str());
	}
	return result;
}

string StringPlus::wrapLongLine(const string& outString, int lineLength)
{
	int stringLength = outString.length();
	int startPosition = 0, currPosition = lineLength;
	string wrapped = "";

	while (currPosition < stringLength) {
		// work backward from lineLength position to find whitespace
		while (outString[currPosition] != ' ' && outString[currPosition] != '\n')
			currPosition--;

		// printout the substring
		wrapped += outString.substr(startPosition, currPosition - startPosition) + '\n';

		// reset for next line
		startPosition = currPosition + 1;
		currPosition = startPosition + lineLength;
	}

	// printout last part 
	wrapped += outString.substr(startPosition, currPosition - startPosition);

	return wrapped;

}

string StringPlus::replaceAll(const string& original, const string& from, const string& to)
{
	string newString = original;  // make a copy
	size_t startPos = 0;

	while ((startPos = newString.find(from, startPos)) != string::npos) // substring was found
		newString.replace(startPos, from.length(), to);

	return newString;
}

string StringPlus::sigFig(double theValue, int figCount)
{
	std::stringstream theStream;
	theStream.precision(figCount);
	theStream << theValue;
	return theStream.str();
}

double StringPlus::getDouble(std::istream& inputStream, const std::string& prompt)
{
	string userInput;
	double output;
	bool allGood = false;
	while (!allGood) { // keep asking until good input
		try {
			std::cout << prompt;
			getline(inputStream, userInput); // take everything
			output = stod(userInput); // "string to double" may cause exception!!!
			allGood = true;
		}
		catch (exception e) {
			std::cout << "ERROR: Unable to convert ->" << userInput
				<< "<- into number" << endl;
			std::cout << "       " << e.what() << endl << endl;
		}
	}
	return output;

}
