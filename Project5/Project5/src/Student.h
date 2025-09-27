#pragma once

#include <iostream>
using namespace std;

class Student
{
private:
	string name;
	string gradeLevel;
	double GPA;

public:
	//default constructor
	Student() : name("unknown"), gradeLevel("unknown"), GPA(0.0)
	{}

	Student(const Student &obj)
		: name(obj.name), gradeLevel(obj.gradeLevel), GPA(obj.GPA)
	{}

	//mutator 
	void setName(string newName)
	{
		name = newName;
	}

	//mutator 
	void setGradeLevel(string newGradeLevel)
	{
		gradeLevel = newGradeLevel;
	}

	//mutator 
	void setGPA(double newGPA)
	{
		GPA = newGPA;
	}

	//overloading operator <<
	friend ostream& operator <<(ostream& outs, const Student& obj)
	{
		outs << obj.name << ", " << obj.gradeLevel << ", " << obj.GPA;
		return outs;
	}

	//overloading operator == 
	friend bool operator ==(const Student& obj1, const Student& obj2)
	{
		if ((obj1.GPA == obj2.GPA) && (obj1.gradeLevel == obj2.gradeLevel) && (obj1.name == obj2.name))
			return true;
		else
			return false;
	}

	//overloading operator <
	friend bool operator <(const Student& obj1, const Student& obj2)
	{
		if (obj1.name < obj2.name)
			return true;
		else
			return false;
	}

};