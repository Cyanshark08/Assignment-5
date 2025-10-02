#include "vectorHandler.h"
#include <iostream>
#include <map>
#include <algorithm>
#include <sstream>
#include <fstream>

/*
* Name: [Partner's Name]
* Date: [Current Date]
* Description: Vector handler implementation using the group's Student class
*/

void vectorHandler::addStudent(const Student& s) {
    students.push_back(s);
}

void vectorHandler::deleteStudent(const Student& s) {
    students.erase(std::remove(students.begin(), students.end(), s), students.end());
}

void vectorHandler::displayStudents() const {
    for (const auto& s : students) {
        std::cout << s << std::endl;  // Uses your operator<<
    }
}

void vectorHandler::displayFrequencies() const {
    std::map<std::string, int> freq;
    for (const auto& s : students) {
        std::stringstream ss;
        ss << s;
        freq[ss.str()]++;
    }
    for (auto& p : freq) {
        std::cout << p.first << " appears " << p.second << " times\n";
    }
}

void vectorHandler::loadFromFile(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
        std::cerr << "Error: could not open " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string name, grade;
        double gpa;

        if (std::getline(ss, name, ',') &&
            std::getline(ss, grade, ',') &&
            (ss >> gpa)) {

            Student s;
            s.setName(name);
            s.setGradeLevel(grade);
            s.setGPA(gpa);
            addStudent(s);
        }
    }
}