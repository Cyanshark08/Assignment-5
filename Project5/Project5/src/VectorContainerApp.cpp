#include "VectorContainerApp.h"
#include "Input.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

/*
* Name: Your Name
* Date: Current Date
* Description: Implementation of Vector Container Application demonstrating
*              STL vector operations including element access, modifiers,
*              iterators, and algorithms.
*/

VectorContainerApp::VectorContainerApp() : SubApp(AppID::VectorContainerApp) {
    m_MenuState = MenuState::Selection;
}

void VectorContainerApp::Run() {
    while (m_MenuState != MenuState::Exited) { 

        std::system("cls");

        // Display menu
        std::cout << "\n\tVectors are sequence containers representing arrays that can change in size.";
        std::cout << "\n\n\t1> Vector's member functions (using STL vector)";
        std::cout << "\n\t" << std::string(110, 205);
        std::cout << "\n\t\tA> clear() - Removes all elements from the vector";
        std::cout << "\n\t\tB> reserve(n) - Requests that the vector capacity be at least enough to contain n elements";
        std::cout << "\n\t\tC> resize(n) - Resizes the container so that it contains n elements";
        std::cout << "\n\t\tD> Read input.dat and push_back(e) - Adds a new element at the end";
        std::cout << "\n\t\tE> pop_back() - Removes the last element in the vector";
        std::cout << "\n\t\tF> front() - Returns a reference to the first element";
        std::cout << "\n\t\tG> back() - Returns a reference to the last element";
        std::cout << "\n\t\tH> index using at() or [] - Returns element at position n";
        std::cout << "\n\t\tI> begin() - Returns iterator pointing to first element";
        std::cout << "\n\t\tJ> end() - Returns iterator referring to past-the-end element";
        std::cout << "\n\t\tK> Using begin() and end() to display all elements";
        std::cout << "\n\t\tL> rbegin() - Returns reverse iterator pointing to last element";
        std::cout << "\n\t\tM> rend() - Returns reverse iterator before first element";
        std::cout << "\n\t\tN> Using rbegin() and rend() to display all elements";
        std::cout << "\n\t\tO> erase(it) - Removes single element using iterator";
        std::cout << "\n\t\tP> erase(start_it,end_it) - Removes range using iterators";
        std::cout << "\n\t\tQ> insert(it, entry) - Insert new entry at iterator";
        std::cout << "\n\t\tR> swap() - Exchanges content with another vector";
        std::cout << "\n\t\tS> Sort - Sorts the vector";
        std::cout << "\n\t" << std::string(110, 196);
        std::cout << "\n\t\t0> Return";
        std::cout << "\n\t" << std::string(110, 205);

        displayVector();
        displayList();
        HandleInput(Input::inputChar("\n\t\tOption: ", "ABCDEFGHIJKLMNOPQRS0"));
    }
}

void VectorContainerApp::Clean() {
    m_Vector.clear();
    m_DemoList.clear();
    m_MenuState = MenuState::Exited;
}

void VectorContainerApp::Restart() {
    m_Vector.clear();
    m_DemoList.clear();
    m_MenuState = MenuState::Selection;
}

void VectorContainerApp::HandleInput(char p_Input) {
    try {
        switch (p_Input) {
        case 'A': clearVector(); break;
        case 'B': reserveVector(); break;
        case 'C': resizeVector(); break;
        case 'D': readFromFile(); break;
        case 'E': popBackVector(); break;
        case 'F': frontBackVector(); break;
        case 'G': frontBackVector(); break; // Handles both F and G
        case 'H': accessElement(); break;
        case 'I': iterateVector(); break;
        case 'J': iterateVector(); break; // Handles both I and J
        case 'K': iterateVector(); break; // Handles display with iterators
        case 'L': reverseIterateVector(); break;
        case 'M': reverseIterateVector(); break; // Handles both L and M
        case 'N': reverseIterateVector(); break; // Handles reverse display
        case 'O': eraseElement(); break;
        case 'P': eraseRange(); break;
        case 'Q': insertElement(); break;
        case 'R': swapVectors(); break;
        case 'S': sortVector(); break;
        case '0':
            m_MenuState = MenuState::Exited;
            return;
        }
    }
    catch (const std::exception& e) {
        std::cout << "\n\t\tERROR: " << e.what();
    }

    std::cout << "\n";
    std::system("pause");
}

/*
* Precondition: Vector may contain elements or be empty
* Postcondition: Vector is empty, all elements are destroyed
*/
void VectorContainerApp::clearVector() {
    m_Vector.clear();
    std::cout << "\n\t\tVector cleared successfully.";
}

/*
* Precondition: Vector exists, n is a positive integer
* Postcondition: Vector capacity is at least n elements
*/
void VectorContainerApp::reserveVector() {
    size_t n = Input::inputInteger("\n\t\tEnter capacity to reserve: ", true);
    m_Vector.reserve(n);
    std::cout << "\n\t\tCapacity reserved: " << n;
    std::cout << "\n\t\tCurrent capacity: " << m_Vector.capacity();
}

/*
* Precondition: Vector exists, n is a positive integer
* Postcondition: Vector size is n, new elements are initialized if size increases
*/
void VectorContainerApp::resizeVector() {
    size_t n = Input::inputInteger("\n\t\tEnter new size: ", true);
    m_Vector.resize(n, Student());
    std::cout << "\n\t\tVector resized to: " << n << " with default values.";
}

/*
* Precondition: Vector is not empty
* Postcondition: Last element is removed from vector, size decreases by 1
*/
void VectorContainerApp::popBackVector() {
    if (!m_Vector.empty()) {
        Student lastElement = m_Vector.back();
        m_Vector.pop_back();
        std::cout << "\n\t\tLast element (" << lastElement << ") popped successfully.";
    }
    else {
        std::cout << "\n\t\tERROR: Vector is empty.";
    }
}

/*
* Precondition: Vector is not empty
* Postcondition: First and last elements are displayed, vector remains unchanged
*/
void VectorContainerApp::frontBackVector() {
    if (!m_Vector.empty()) {
        std::cout << "\n\t\tFront element: " << m_Vector.front();
        std::cout << "\n\t\tBack element: " << m_Vector.back();
    }
    else {
        std::cout << "\n\t\tERROR: Vector is empty.";
    }
}

/*
* Precondition: Vector is not empty, index is within valid range
* Postcondition: Element at specified index is displayed, vector remains unchanged
*/
void VectorContainerApp::accessElement() {
    if (m_Vector.empty()) {
        std::cout << "\n\t\tERROR: Vector is empty.";
        return;
    }
    size_t index = Input::inputInteger("\n\t\tEnter index: ", 0, (int)m_Vector.size() - 1);
    char choice = Input::inputChar("\t\tUse at() (A) or operator[] (B)? ", "AB");
    if (choice == 'A') {
        std::cout << "\n\t\tElement at index " << index << ": " << m_Vector.at(index);
    }
    else {
        std::cout << "\n\t\tElement at index " << index << ": " << m_Vector[index];
    }
}

/*
* Precondition: Vector exists
* Postcondition: All elements are displayed using iterators, vector remains unchanged
*/
void VectorContainerApp::iterateVector() {
    if (m_Vector.empty()) {
        std::cout << "\n\t\tERROR: Vector is empty.";
        return;
    }

    std::cout << "\n\t\tElements using begin() and end(): ";
    for (auto it = m_Vector.begin(); it != m_Vector.end(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << "\n\t\tbegin() points to: " << *m_Vector.begin();
    std::cout << "\n\t\tend() points past the last element";
}

/*
* Precondition: Vector exists and is not empty
* Postcondition: All elements are displayed in reverse order using reverse iterators
*/
void VectorContainerApp::reverseIterateVector() {
    if (m_Vector.empty()) {
        std::cout << "\n\t\tERROR: Vector is empty.";
        return;
    }

    std::cout << "\n\t\tElements in reverse using rbegin() and rend(): ";
    for (auto it = m_Vector.rbegin(); it != m_Vector.rend(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << "\n\t\trbegin() points to: " << *m_Vector.rbegin();
    std::cout << "\n\t\trend() points before first element";
}

/*
* Precondition: Vector is not empty, index is valid
* Postcondition: Element at specified position is removed, size decreases by 1
*/
void VectorContainerApp::eraseElement() {
    if (m_Vector.empty()) {
        std::cout << "\n\t\tERROR: Vector is empty.";
        return;
    }
    size_t index = Input::inputInteger("\n\t\tEnter index to erase: ", 0, (int)m_Vector.size() - 1);
    auto it = m_Vector.begin();
    std::advance(it, index);
    Student erasedValue = *it;
    m_Vector.erase(it);
    std::cout << "\n\t\tElement " << erasedValue << " at index " << index << " erased successfully.";
}

/*
* Precondition: Vector is not empty, start and end indices are valid
* Postcondition: Elements in specified range are removed, size decreases accordingly
*/
void VectorContainerApp::eraseRange() {
    if (m_Vector.empty()) {
        std::cout << "\n\t\tERROR: Vector is empty.";
        return;
    }
    size_t start = Input::inputInteger("\n\t\tEnter start index: ", 0, (int)m_Vector.size() - 1);
    size_t end = Input::inputInteger("\t\tEnter end index: ", (int)start, (int)m_Vector.size() - 1);

    auto start_it = m_Vector.begin();
    std::advance(start_it, start);
    auto end_it = m_Vector.begin();
    std::advance(end_it, end + 1);

    m_Vector.erase(start_it, end_it);
    std::cout << "\n\t\tElements from index " << start << " to " << end << " erased successfully.";
}

/*
* Precondition: Vector exists, index is valid (0 to size)
* Postcondition: New element is inserted at specified position, size increases by 1
*/
void VectorContainerApp::insertElement() {
    /*if (m_Vector.empty()) {
        std::cout << "\n\t\tERROR: Vector is empty.";
        return;
    }*/
    size_t index = Input::inputInteger("\n\t\tEnter index to insert at: ", 0, (int)m_Vector.size());
    Student temp = this->getStudent();

    auto it = m_Vector.begin();
    std::advance(it, index);
    m_Vector.insert(it, temp);

    std::cout << "\n\t\tValue " << temp << " inserted at index " << index;
}

/*
* Precondition: Two vectors exist
* Postcondition: Contents of the two vectors are exchanged
*/
void VectorContainerApp::swapVectors() {
    std::vector<Student> otherVector;
    otherVector.push_back(Student());
    otherVector.push_back(Student());
    otherVector.push_back(Student());

    std::cout << "\n\t\tBefore swap - Current vector: ";
    for (const auto& elem : m_Vector) std::cout << elem << " ";
    std::cout << "\n\t\tBefore swap - Other vector: ";
    for (const auto& elem : otherVector) std::cout << elem << " ";

    m_Vector.swap(otherVector);

    std::cout << "\n\t\tAfter swap - Current vector: ";
    for (const auto& elem : m_Vector) std::cout << elem << " ";
    std::cout << "\n\t\tAfter swap - Other vector: ";
    for (const auto& elem : otherVector) std::cout << elem << " ";
}

/*
* Precondition: Vector contains comparable elements
* Postcondition: Vector elements are sorted in ascending order
*/
void VectorContainerApp::sortVector() {
    if (m_Vector.empty()) {
        std::cout << "\n\t\tERROR: Vector is empty.";
        return;
    }

    std::cout << "\n\t\tBefore sorting: ";
    for (const auto& elem : m_Vector) std::cout << elem << " ";

    std::sort(m_Vector.begin(), m_Vector.end());

    std::cout << "\n\t\tAfter sorting: ";
    for (const auto& elem : m_Vector) std::cout << elem << " ";
}

/*
* Precondition: input.dat file exists and contains valid integers
* Postcondition: Elements from file are added to vector using push_back
*/
void VectorContainerApp::readFromFile() {
    //std::ifstream file("input.dat");
    //if (!file) {
    //    std::cout << "\n\t\tERROR: Could not open input.dat file.";
    //    return;
    //}

    //int count = 0;
    //while (file >> value) {
    //    m_Vector.push_back(value);
    //    count++;
    //}
    //file.close();

    //std::cout << "\n\t\tSuccessfully read " << count << " elements from input.dat";

    //// Also demonstrate list operations
    //m_DemoList.assign(m_Vector.begin(), m_Vector.end());
    //std::cout << "\n\t\tAlso created a list with the same elements for demonstration.";
    return;
}

void VectorContainerApp::displayVector() const {
    std::cout << "\n\n\tCurrent Vector: ";
    if (m_Vector.empty()) {
        std::cout << "Empty";
    }
    else {
        std::cout << "[ ";
        for (size_t i = 0; i < m_Vector.size(); ++i) {
            std::cout << m_Vector[i];
            if (i < m_Vector.size() - 1) std::cout << ", ";
        }
        std::cout << " ]";
    }
    std::cout << "\n\tSize: " << m_Vector.size() << ", Capacity: " << m_Vector.capacity();
}

void VectorContainerApp::displayList() const {
    std::cout << "\n\tDemo List (STL): ";
    if (m_DemoList.empty()) {
        std::cout << "Empty";
    }
    else {
        std::cout << "[ ";
        for (const auto& elem : m_DemoList) {
            std::cout << elem << " ";
        }
        std::cout << "]";
    }
    std::cout << "\n\tList Size: " << m_DemoList.size();
}

Student VectorContainerApp::getStudent() const
{
    // get student info
    std::string name = Input::inputString("\n\t\tEnter a new student name: ", true);
    int level = Input::inputInteger("\t\tEnter their grade level (1-Freshman, 2-Sophmore, 3-Junior, or 4-Senior): ", 1, 4);
    double gpa = Input::inputDouble("\t\tEnter their gpa (0.0...4.0): ", 0.0, 4.0);

    // set the student
    std::string levels[4] = { "Freshmen", "Sophmore", "Junior", "Senior" };

    Student temp;
    temp.setName(name);
    temp.setGradeLevel(levels[level - 1]);
    temp.setGPA(gpa);

    return temp;
}