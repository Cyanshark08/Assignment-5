#pragma once
#ifndef CONTAINER_HANDLER_H
#define CONTAINER_HANDLER_H

#include "Student.h"  // Use YOUR Student.h

class containerHandler {
public:
    virtual ~containerHandler() = default;
    virtual void addStudent(const Student& s) = 0;  // Use your Student class
    virtual void deleteStudent(const Student& s) = 0;
    virtual void displayStudents() const = 0;
    virtual void displayFrequencies() const = 0;
    virtual void loadFromFile(const std::string& filename) = 0;
};

#endif