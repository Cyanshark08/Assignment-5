#pragma once
#ifndef LIST_HANDLER_H
#define LIST_HANDLER_H

#include "containerHandler.h"
#include "Student.h"  // Use YOUR Student.h
#include <list>

class listHandler : public containerHandler {
private:
    std::list<Student> students;

public:
    void addStudent(const Student& s) override;
    bool deleteStudent(const Student& s) override;  // Changed to return bool
    void displayStudents() const override;
    void displayFrequencies() const override;
    void loadFromFile(const std::string& filename) override;
};

#endif