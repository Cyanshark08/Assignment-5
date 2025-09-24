#pragma once
#include <string>

class ExceptionInterface
{
public:
	std::string Message() const;

private:
	virtual std::string GetExceptionName() const = 0;
	virtual std::string GetExceptionMessage() const = 0;
};

