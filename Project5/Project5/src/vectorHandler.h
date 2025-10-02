#pragma once
#ifndef VECTOR_HANDLER_H
#define VECTOR_HANDLER_H

#include "containerHandler.h"
#include "Student.h"  // Use YOUR Student.h
#include <vector>

class vectorHandler : public containerHandler {
private:
    std::vector<Student> students;

public:
    void addStudent(const Student& s) override;
    bool deleteStudent(const Student& s) override;  // Changed to return bool
    void displayStudents() const override;
    void displayFrequencies() const override;
    void loadFromFile(const std::string& filename) override;
};

#endif