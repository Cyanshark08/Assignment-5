#pragma once
#include "SubApp.h"
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
class DoublyListApp :
    public SubApp
{
public:
    enum class MenuState
    {
        Exited,
        Selection
    };

public:
    explicit DoublyListApp(string path = "input.dat") : filePath(std::move(path)), m_MenuState(MenuState::Selection) {}

    // Pre: none
    // Post: runs until user selects '0'
    void Run() override;

    void Clean() override;

    void Restart() override;

private:
    void HandleInput(char p_Input) override;
    MenuState m_MenuState;

private:
    list<Student> L;       // std::list == doubly linked list
    string filePath;

    // NEW: holds one-line status shown above the menu (e.g., after resize)
    string statusMsg;

    // UI
    void showMenu() const;
    void print(const string &title = "List contents") const;

    // helpers
    list<Student>::iterator iterAt(size_t pos);
    static Student promptStudent();
    static bool parseStudentLine(const string &line, Student &s);
    static Student placeholderStudent();          // safe placeholder when growing
    bool loadFromFileFront();                     // push_front from file
    bool loadFromFileBack();                      // push_back  from file


};

