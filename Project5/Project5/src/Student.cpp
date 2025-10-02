#include "Student.h"
#include <fstream>

//default constructor
Student::Student() : name("unknown"), gradeLevel("unknown"), GPA(0.0)
{
}

Student::Student(const Student& obj)
	: name(obj.name), gradeLevel(obj.gradeLevel), GPA(obj.GPA)
{
}

Student::Student(const std::string& p_Name, const std::string& p_GradeLevel, double p_GPA)
	: name(p_Name),
	gradeLevel(p_GradeLevel),
	GPA(p_GPA)
{}

//mutator 
void Student::setName(const std::string& newName)
{
	name = newName;
}

//mutator 
void Student::setGradeLevel(const std::string& newGradeLevel)
{
	gradeLevel = newGradeLevel;
}

//mutator 
void Student::setGPA(double newGPA)
{
	GPA = newGPA;
}

std::string Student::getName() const
{
	return name;
}

bool Student::operator==(const Student& p_Other) const
{
	return ((this->GPA == p_Other.GPA) && (this->gradeLevel == p_Other.gradeLevel) && (this->name == p_Other.name));
}

bool Student::operator<(const Student& p_Other) const
{
	return (this->name < p_Other.name);
}

Student& Student::operator=(const Student& p_Other)
{
	this->name = p_Other.name;
	this->gradeLevel = p_Other.gradeLevel;
	this->GPA = p_Other.GPA;

	return *this;
}

//overloading operator <<
std::ostream& operator<<(std::ostream& outs, const Student& obj)
{
	outs << obj.name << ", " << obj.gradeLevel << ", " << obj.GPA;
	return outs;
}

