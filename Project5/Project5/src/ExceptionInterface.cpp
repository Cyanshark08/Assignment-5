#include "ExceptionInterface.h"
#include <sstream>

std::string ExceptionInterface::Message() const
{
	std::stringstream ss;
	ss << "\n\tEXCEPTION ERROR (" << GetExceptionName() << ") : " << GetExceptionMessage() << "\n\n\t";
	return ss.str();
}