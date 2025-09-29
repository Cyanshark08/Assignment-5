// main.cpp
// CMPR131 – Assignment 5 (compact OOP, first menu shows only Option 3)

#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include "ListApp.h"
#include "Student.h"

using namespace std;

static void drawMain() {
    system("cls");
    cout << "\n\tCMPR131 Chapter 5: Vector and List Container by Tony\n";
    cout << "\t" << string(80, char(205)) << "\n"; // double line
    cout << "\t 3> Application using Vector and/or List container\n";
    cout << "\t" << string(80, char(196)) << "\n"; // single line
    cout << "\t 0> Exit\n";
    cout << "\t" << string(80, char(205)) << "\n\n";
    cout << "\tOption: ";
}

// Best option: portable file-exists check using <fstream>
static string chooseDataFile() {
    ifstream f1("input.dat");
    if (f1.good()) return "input.dat";
    ifstream f2("input (1).dat");
    if (f2.good()) return "input (1).dat";
    return "input.dat"; // default
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const string dataFile = chooseDataFile();

    char choice;
    do {
        drawMain();
        cin >> choice;

        switch (choice) {
        case '3': {
            ListApp app(dataFile);   // Second menu runs inside
            app.run();
            break;
        }
        case '0':
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid option.\n";
            break;
        }
    } while (choice != '0');

    return 0;
}
