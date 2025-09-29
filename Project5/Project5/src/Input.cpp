#include "Input.h"

//PreCondition: spaces (boolean true or false)
//PostCondition: returns a std::string including space character(s) or without space character 
std::string Input::inputString(const std::string& prompt, bool spaces)
{
	std::string input = "";

	std::cout << prompt;
	if (spaces)
		getline(std::cin, input);
	else
	{
		std::cin >> input;
		std::cin.clear();
		std::cin.ignore(999, '\n');
	}
	return input;
}

//PreCondition: valid std::string of options
//PostCondition: returns an uppercase  of the option (char)
char Input::inputChar(const std::string& prompt, const std::string& options)
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
		else
		{
			bool found = false;
			for (int i = 0; i < options.length(); i++)
				if ((std::toupper(options.at(i))) == std::toupper(input))
				{
					found = true;
					break;
				}
			if (found)
			{
				std::cin.clear();
				std::cin.ignore(999, '\n');
				break;
			}
			else
				std::cout << "ERROR: Invalid input. Must be one of '" << options << "' character.\n";
		}
	} while (true);
	return std::toupper(input);
}

//PreCondition: valid yes (char) or no (char)
//PostCondition: returns an uppercase  yes (char) or no (char) 
char Input::inputChar(const std::string& prompt, char yes, char no)
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
		else if (tolower(input) != tolower(yes) && tolower(input) != tolower(no))
			std::cout << "ERROR: Invalid input. Must be a '" << static_cast<char>(std::toupper(yes)) << "' or '" << static_cast<char>(std::toupper(no)) << "' character.\n";
		else
		{
			std::cin.clear();
			std::cin.ignore(999, '\n');
			break;
		}
	} while (true);
	return std::toupper(input);
}

//PreCondition: NA
//PostCondition: returns any character
char Input::inputChar(const std::string& prompt)
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
		else
			break;
	} while (true);
	std::cin.clear();
	std::cin.ignore(999, '\n');
	return std::toupper(input);
}

//PreCondition: NA
//PostCondition: returns any integer value
int Input::inputInteger(const std::string& prompt)
{
	int input;
	do
	{
		std::cout << prompt;
		if (!(std::cin >> input))
		{
			std::cout << "ERROR: Invalid input. Must be an integer type.\n";
			std::cin.clear();
			std::cin.ignore(999, '\n');
		}
		else
			break;
	} while (true);
	std::cin.clear();
	std::cin.ignore(999, '\n');
	return input;
}

//PreCondition: posNeg (boolean true or false)
//PostCondition: returns a positive integer value (posNeg = true) or a negative integer value (poseNeg = false)
int Input::inputInteger(const std::string& prompt, bool posNeg)
{
	int input;
	do
	{
		std::cout << prompt;
		if (!(std::cin >> input))
		{
			std::cout << "ERROR: Invalid input. Must be an integer type.\n";
			std::cin.clear();
			std::cin.ignore(999, '\n');
		}
		else if (posNeg && input <= 0)
			std::cout << "ERROR: Invalid input. Must be a positive number.\n";
		else if (!posNeg && input >= 0)
			std::cout << "ERROR: Invalid input. Must be a negative number.\n";
		else
			break;
	} while (true);
	std::cin.clear();
	std::cin.ignore(999, '\n');
	return input;
}

//PreCondition: start (integer) and greater (boolean true or false)
//PostCondition: returns an integer value greater than start or lesser than start
int Input::inputInteger(const std::string& prompt, int start, bool greater)
{
	int input;
	do
	{
		std::cout << prompt;
		if (!(std::cin >> input))
		{
			std::cout << "ERROR: Invalid input. Must be an integer type.\n";
			std::cin.clear();
			std::cin.ignore(999, '\n');
		}
		else if (greater && input < start)
			std::cout << "ERROR: Invalid input. Must be a greater than or equal to " << start << ".\n";
		else if (!greater && input > start)
			std::cout << "ERROR: Invalid input. Must be a lesser than or equal to " << start << ".\n";
		else
			break;
	} while (true);
	std::cin.clear();
	std::cin.ignore(999, '\n');
	return input;
}

//PreCondition: startRange (integer) and endRange (integer)
//PostCondition: returns an integer value within range (startRannge and endRange)
int Input::inputInteger(const std::string& prompt, int startRange, int endRange)
{
	int input;
	do
	{
		std::cout << prompt;
		if (!(std::cin >> input))
		{
			std::cout << "ERROR: Invalid input. Must be an integer type.\n";
			std::cin.clear();
			std::cin.ignore(999, '\n');
		}
		else if (!(input >= std::min(startRange, endRange) && input <= std::max(startRange, endRange)))
			std::cout << "ERROR: Invalid input. Must be from " << startRange << ".." << endRange << ".\n";
		else
			break;
	} while (true);
	std::cin.clear();
	std::cin.ignore(999, '\n');
	return input;
}

//PreCondition: NA
//PostCondition: returns any double value
double Input::inputDouble(const std::string& prompt)
{
	double input;
	do
	{
		std::cout << prompt;
		if (!(std::cin >> input))
		{
			std::cout << "ERROR: Invalid input. Must be a double type.\n";
			std::cin.clear();
			std::cin.ignore(999, '\n');
		}
		else
			break;
	} while (true);
	std::cin.clear();
	std::cin.ignore(999, '\n');
	return input;
}

//PreCondition: posNeg (boolean true or false)
//PostCondition: returns a positive double value (posNeg = true) or a negative double value (poseNeg = false)
double Input::inputDouble(const std::string& prompt, bool posNeg)
{
	double input;
	do
	{
		std::cout << prompt;
		if (!(std::cin >> input))
		{
			std::cout << "ERROR: Invalid input. Must be a double type.\n";
			std::cin.clear();
			std::cin.ignore(999, '\n');
		}
		else if (posNeg && input <= 0.0)
			std::cout << "ERROR: Invalid input. Must be a positive number.\n";
		else if (!posNeg && input >= 0.0)
			std::cout << "ERROR: Invalid input. Must be a negative number.\n";
		else
			break;
	} while (true);
	std::cin.clear();
	std::cin.ignore(999, '\n');
	return input;
}

//PreCondition: start(integer) and greater(boolean true or false)
//PostCondition: returns an integer value greater than start or lesser than start
double Input::inputDouble(const std::string& prompt, double start, bool posNeg)
{
	double input;
	do
	{
		std::cout << prompt;
		if (!(std::cin >> input))
		{
			std::cout << "ERROR: Invalid input. Must be a double type.\n";
			std::cin.clear();
			std::cin.ignore(999, '\n');
		}
		else if (posNeg && input <= start)
			std::cout << "ERROR: Invalid input. Must be greater than or equal to " << start << ".\n";
		else if (!posNeg && input >= start)
			std::cout << "ERROR: Invalid input. Must be lesser than or equal to " << start << ".\n";
		else
			break;
	} while (true);
	std::cin.clear();
	std::cin.ignore(999, '\n');
	return input;
}

//PreCondition: startRange (integer) and endRange (integer)
//PostCondition: returns an integer value within range (startRannge and endRange)
double Input::inputDouble(const std::string& prompt, double startRange, double endRange)
{
	double input;
	do
	{
		std::cout << prompt;
		if (!(std::cin >> input))
		{
			std::cout << "ERROR: Invalid input. Must be a double type.\n";
			std::cin.clear();
			std::cin.ignore(999, '\n');
		}
		else if (!(input >= std::min(startRange, endRange) && input <= std::max(startRange, endRange)))
			std::cout << "ERROR: Invalid input. Must be from " << startRange << ".." << endRange << ".\n";
		else
			break;
	} while (true);
	std::cin.clear();
	std::cin.ignore(999, '\n');
	return input;
}

// PreCondition: prompt is passed as an argument
// PostCondition: returns a c-std::string date in the proper format
std::string Input::inputDate(const std::string& prompt)
{
	std::string date;
	do
	{
		bool validDate = true;

		std::cout << prompt;
		std::getline(std::cin, date);
		if (std::cin.fail())
		{
			std::cout << "ERROR: Invalid input. Input must be a c-string.\n";
			std::cin.clear();
			std::cin.ignore(999, '\n');
			continue;
		}

		else if (date.length() != 10)
		{
			std::cout << "ERROR: Invalid date. Date is not 10 characters.\n";
			continue;
		}


		else if (date[2] != '/' || date[5] != '/')
		{
			std::cout << "ERROR: Invalid date. Date does not contain the '/' delimiter.\n";
			continue;
		}

		for (int i = 0; i < 11; i++)
		{
			if (i == 2 || i == 5)
				continue;
			if (!isdigit(date[i]))
			{
				std::cout << "ERROR: Invalid date. Date contains non-digit characters.\n";
				validDate = false;
				break;
			}
		}

		if (!validDate) continue;

		int month = ((date[0] - '0') * 10) + (date[1] - '0');
		int day = ((date[3] - '0') * 10) + (date[4] - '0');

		if (month < 1 || month > 12)
		{
			std::cout << "ERROR: Invalid month (" << month << ") is out of range (1...12).\n";
			continue;
		}

		switch (month)
		{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12: // 31 days
		{
			if (day < 1 || day > 31)
			{
				std::cout << "ERROR: Invalid day (" << day << ") is out of range. (1...31)\n";
				continue;
			}
			break;
		}

		case 4: case 6: case 9: case 11: // 30 days
		{
			if (day < 1 || day > 30)
			{
				std::cout << "ERROR: Invalid day (" << day << ") is out of range. (1...30)\n";
				continue;
			}
			break;
		}

		case 2: // 29 days
		{
			if (day < 1 || day > 29)
			{
				std::cout << "ERROR: Invalid day (" << day << ") is out of range. (1...29)\n";
				continue;
			}
			break;
		}

		default:
			std::cout << "ERROR: Month does not exist.\n";
		}

		break;
	} while (true);

	return date;
}
