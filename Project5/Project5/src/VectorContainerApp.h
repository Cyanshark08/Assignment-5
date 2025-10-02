#pragma once
#include "SubApp.h"
#include "Student.h"
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

/*
* Name: Your Name
* Date: Current Date
* Description: Vector Container Application demonstrating STL vector operations
*              including element access, modifiers, iterators, and algorithms.
*/

class VectorContainerApp : public SubApp {
public:
    enum class MenuState {
        Exited,
        Selection
    };

    VectorContainerApp();
    void Run() override;
    void Clean() override;
    void Restart() override;

private:
    void HandleInput(char p_Input) override;
    void displayVector() const;
    void displayList() const;
    void readFromFile();

    // Vector operations with pre/post conditions
    void clearVector();
    void reserveVector();
    void resizeVector();
    void popBackVector();
    void frontBackVector();
    void accessElement();
    void beginIterator();        // For option I
    void endIterator();          // For option J
    void displayWithIterators(); // For option K
    void rbeginIterator();       // For option L
    void rendIterator();         // For option M
    void displayWithReverseIterators(); // For option N
    void eraseElement();         // For option O
    void eraseRange();           // For option P
    void insertElement();        // For option Q
    void swapVectors();          // For option R
    void sortVector();           // For option S
    Student getStudent() const;

private:
    MenuState m_MenuState;
    std::vector<Student> m_Vector;
    std::list<int> m_DemoList; // For demonstration purposes
};