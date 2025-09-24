#pragma once

#include <iostream>
#include <algorithm>
#include <string>

namespace Input {

	//PreCondition: spaces (boolean true or false)
	//PostCondition: returns a std::string including space character(s) or without space character 
	std::string inputString(const std::string& prompt, bool spaces);

	//PreCondition: valid std::string of options
	//PostCondition: returns an uppercase  of the option (char)
	char inputChar(const std::string& prompt, const std::string& options);

	//PreCondition: valid yes (char) or no (char)
	//PostCondition: returns an uppercase  yes (char) or no (char) 
	char inputChar(const std::string& prompt, char yes, char no);

	//PreCondition: alphaOrDigit (boolean true or false)
	//PostCondition: returns an alphabet or a digit character
	/*char inputChar(const std::string& prompt, bool alphaOrDigit)
	{
		char input;
		do
		{
			std::cout << prompt;
			if (!(std::cin >> input))
			{
				std::cout << "ERROR: Invalid input. Must be a character type.\n";
				std::cin.clear();
				std::cin.ignore(999, '\n');
			}
			else if (alphaOrDigit && !isalpha(input))
				std::cout << "ERROR: Invalid input. Must be an alphabet character.\n";
			else if (!alphaOrDigit && !isdigit(input))
				std::cout << "ERROR: Invalid input. Must be a digit character.\n";
			else
			{
				std::cin.clear();
				std::cin.ignore(999, '\n');
				break;
			}
		} while (true);
		return input;
	} */

	//PreCondition: NA
	//PostCondition: returns any character
	char inputChar(const std::string& prompt);

	//PreCondition: NA
	//PostCondition: returns any integer value
	int inputInteger(const std::string& prompt);

	//PreCondition: posNeg (boolean true or false)
	//PostCondition: returns a positive integer value (posNeg = true) or a negative integer value (poseNeg = false)
	int inputInteger(const std::string& prompt, bool posNeg);

	//PreCondition: start (integer) and greater (boolean true or false)
	//PostCondition: returns an integer value greater than start or lesser than start
	int inputInteger(const std::string& prompt, int start, bool greater);

	//PreCondition: startRange (integer) and endRange (integer)
	//PostCondition: returns an integer value within range (startRannge and endRange)
	int inputInteger(const std::string& prompt, int startRange, int endRange);

	//PreCondition: NA
	//PostCondition: returns any double value
	double inputDouble(const std::string& prompt);

	//PreCondition: posNeg (boolean true or false)
	//PostCondition: returns a positive double value (posNeg = true) or a negative double value (poseNeg = false)
	double inputDouble(const std::string& prompt, bool posNeg);

	//PreCondition: start(integer) and greater(boolean true or false)
	//PostCondition: returns an integer value greater than start or lesser than start
	double inputDouble(const std::string& prompt, double start, bool posNeg);

	//PreCondition: startRange (integer) and endRange (integer)
	//PostCondition: returns an integer value within range (startRannge and endRange)
	double inputDouble(const std::string& prompt, double startRange, double endRange);

	// PreCondition: prompt is passed as an argument
	// PostCondition: returns a c-std::string date in the proper format
	std::string inputDate(const std::string& prompt);
}
