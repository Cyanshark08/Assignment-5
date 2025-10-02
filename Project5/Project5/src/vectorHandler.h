#pragma once
#ifndef VECTOR_HANDLER_H
#define VECTOR_HANDLER_H

#include "containerHandler.h"
#include "Student.h"  // Use YOUR Student.h
#include <vector>

class vectorHandler : public containerHandler {
private:
    std::vector<Student> students;  // Use your Student class

public:
    void addStudent(const Student& s) override;
    void deleteStudent(const Student& s) override;
    void displayStudents() const override;
    void displayFrequencies() const override;
    void loadFromFile(const std::string& filename) override;
};

#endif