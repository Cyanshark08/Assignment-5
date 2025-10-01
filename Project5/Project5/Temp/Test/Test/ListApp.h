// ListApp.h
// Doubly Linked List application using std::list<student>

#ifndef LIST_APP_H
#define LIST_APP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <cctype>
#include <stdexcept>
#include "Student.h"

using namespace std;

class ListApp {
    list<student> L;       // std::list == doubly linked list
    string filePath;

    // NEW: holds one-line status shown above the menu (e.g., after resize)
    string statusMsg;

    // UI
    void showMenu() const;
    void print(const string& title = "List contents") const;

    // helpers
    list<student>::iterator iterAt(size_t pos);
    static student promptStudent();
    static bool parseStudentLine(const string& line, student& s);
    static size_t askSizeT_1_100();               // reads size in [1..100]
    static student placeholderStudent();          // safe placeholder when growing
    bool loadFromFileFront();                     // push_front from file
    bool loadFromFileBack();                      // push_back  from file

public:
    explicit ListApp(string path = "input.dat") : filePath(std::move(path)) {}

    // Pre: none
    // Post: runs until user selects '0'
    void run();
};

#endif
