#pragma once

#include <iostream>
#include <limits>
#include "string"
#include <unordered_map>

class Student
{
public:
	//default constructor
	Student();

	Student(const Student &obj);

	Student(const std::string& p_Name, const std::string& p_GradeLevel, double p_GPA);

	//mutator 
	void setName(const std::string& newName);

	//mutator 
	void setGradeLevel(const std::string& newGradeLevel);

	//mutator 
	void setGPA(double newGPA);

	std::string getName() const;

	//overloading operator <<
	friend std::ostream& operator <<(std::ostream& outs, const Student& obj);

	//overloading operator == 
	bool operator==(const Student& p_Other) const;

	//overloading operator <
	bool operator<(const Student& p_Other) const;

	//overloading operator == 
	Student& operator=(const Student& p_Other);

private:
	std::string name;
	std::string gradeLevel;
	double GPA;

};