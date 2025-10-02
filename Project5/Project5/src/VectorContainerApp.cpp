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
        case 'I': beginIterator(); break;    // Shows iterator to first element
        case 'J': endIterator(); break;      // Shows iterator to past-the-end element
        case 'K': displayWithIterators(); break; // Shows all elements with addresses
        case 'L': rbeginIterator(); break;   // Shows reverse iterator to last element
        case 'M': rendIterator(); break;     // Shows reverse iterator before first element
        case 'N': displayWithReverseIterators(); break; // Shows all elements in reverse with addresses
        case 'O': eraseElement(); break;     // Removes single element using iterator
        case 'P': eraseRange(); break;       // Removes range using iterators
        case 'Q': insertElement(); break;    // Insert new entry at iterator
        case 'R': swapVectors(); break;      // Exchanges content with another vector
        case 'S': sortVector(); break;       // Sorts the vector
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
* Precondition: Vector exists and is not empty
* Postcondition: Iterator to first element is displayed with address
*/
void VectorContainerApp::beginIterator() {
    if (m_Vector.empty()) {
        std::cout << "\n\t\tERROR: Vector is empty.";
        return;
    }

    // Get iterator to first element and display its address
    auto it = m_Vector.begin();
    Student* ptr = &(*it);

    std::cout << "\n\t\tThe iterator referring the first element: " << ptr << "(" << *it << ")";
}

/*
* Precondition: Vector exists and is not empty
* Postcondition: Iterator to past-the-end element is displayed with address
*/
void VectorContainerApp::endIterator() {
    if (m_Vector.empty()) {
        std::cout << "\n\t\tERROR: Vector is empty.";
        return;
    }

    // Get iterator to past-the-end element (cannot dereference it)
    auto it = m_Vector.end();
    Student* ptr = &(*(m_Vector.begin())) + m_Vector.size(); // Calculate past-the-end address

    std::cout << "\n\t\tThe iterator referring to the past-the-end element: " << ptr;
}

/*
* Precondition: Vector exists
* Postcondition: All elements are displayed using iterators with their addresses
*/
void VectorContainerApp::displayWithIterators() {
    if (m_Vector.empty()) {
        std::cout << "\n\t\tERROR: Vector is empty.";
        return;
    }

    std::cout << "\n\t\tUsing begin() and end(), the vector contains:";
    int index = 0;
    for (auto it = m_Vector.begin(); it != m_Vector.end(); ++it, ++index) {
        Student* ptr = &(*it);
        std::cout << "\n\t\t" << ptr << " (" << *it << ")";
    }
}

/*
* Precondition: Vector exists and is not empty
* Postcondition: Reverse iterator to last element is displayed with address and data
*/
void VectorContainerApp::rbeginIterator() {
    if (m_Vector.empty()) {
        std::cout << "\n\t\tERROR: Vector is empty.";
        return;
    }

    // Get reverse iterator to last element and display its address and data
    auto it = m_Vector.rbegin();
    Student* ptr = &(*it);

    std::cout << "\n\t\tThe reverse iterator pointing to the last element: " << ptr << "(" << *it << ")";
}

/*
* Precondition: Vector exists and is not empty
* Postcondition: Reverse iterator to theoretical element before first is displayed with address
*/
void VectorContainerApp::rendIterator() {
    if (m_Vector.empty()) {
        std::cout << "\n\t\tERROR: Vector is empty.";
        return;
    }

    // Get reverse iterator to theoretical element before first (cannot dereference it)
    auto it = m_Vector.rend();

    // Calculate the address for rend() (theoretical element before first)
    Student* firstElementPtr = &(m_Vector.front());
    Student* rendPtr = firstElementPtr - 1; // Theoretical position before first

    std::cout << "\n\t\tThe reverse iterator pointing to the theoretical element preceding the first element in the vector: " << rendPtr;
}

/*
* Precondition: Vector exists and is not empty
* Postcondition: All elements are displayed in reverse order using reverse iterators with addresses
*/
void VectorContainerApp::displayWithReverseIterators() {
    if (m_Vector.empty()) {
        std::cout << "\n\t\tERROR: Vector is empty.";
        return;
    }

    std::cout << "\n\t\tElements in reverse using rbegin() and rend(): \n";
    int index = m_Vector.size() - 1;
    for (auto it = m_Vector.rbegin(); it != m_Vector.rend(); ++it, --index) {
        Student* ptr = &(*it);
        std::cout << "\t\t[" << index << "] " << ptr << " (" << *it << ")\n";
    }
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

    // Get the address of the element to be erased
    Student* ptr = &(*it);

    Student erasedValue = *it;
    m_Vector.erase(it);

    std::cout << "\n\t\tAn element after the begin iterator " << ptr << " has been removed.";
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

    // Get addresses before erasing
    Student* start_ptr = &(*start_it);
    Student* end_ptr = &(*(m_Vector.begin())) + m_Vector.size(); // Calculate end address

    m_Vector.erase(start_it, end_it);

    std::cout << "\n\t\tALL elements starting at begin iterator " << start_ptr << " and going up to end iterator " << end_ptr << " have been removed";
}

/*
* Precondition: Vector exists, index is valid (0 to size)
* Postcondition: New element is inserted at specified position, size increases by 1
*/
void VectorContainerApp::insertElement() {
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
    // Create another vector with some sample data
    std::vector<Student> otherVector;

    // Add some sample students to the other vector
    Student s1, s2, s3;
    s1.setName("John Doe"); s1.setGradeLevel("Senior"); s1.setGPA(3.8);
    s2.setName("Jane Smith"); s2.setGradeLevel("Junior"); s2.setGPA(3.9);
    s3.setName("Bob Wilson"); s3.setGradeLevel("Sophomore"); s3.setGPA(3.2);

    otherVector.push_back(s1);
    otherVector.push_back(s2);
    otherVector.push_back(s3);

    std::cout << "\n\t\tvector (v2) is initially empty.";
    std::cout << "\n\t\tvector (v1) is empty after swapped with vector (v2).";
    std::cout << "\n\t\tvector (v2) after swapped with vector (v1).";

    // Display current vector before swap
    std::cout << "\n\n\t\tCurrent vector before swap:";
    if (m_Vector.empty()) {
        std::cout << "\n\t\t\t[Empty]";
    }
    else {
        for (size_t i = 0; i < m_Vector.size(); ++i) {
            std::cout << "\n\t\t\t[" << i << "] " << m_Vector[i];
        }
    }

    // Display other vector before swap
    std::cout << "\n\n\t\tOther vector before swap:";
    if (otherVector.empty()) {
        std::cout << "\n\t\t\t[Empty]";
    }
    else {
        for (size_t i = 0; i < otherVector.size(); ++i) {
            std::cout << "\n\t\t\t[" << i << "] " << otherVector[i];
        }
    }

    // Perform the swap
    m_Vector.swap(otherVector);

    // Display current vector after swap
    std::cout << "\n\n\t\tCurrent vector after swap:";
    if (m_Vector.empty()) {
        std::cout << "\n\t\t\t[Empty]";
    }
    else {
        for (size_t i = 0; i < m_Vector.size(); ++i) {
            std::cout << "\n\t\t\t[" << i << "] " << m_Vector[i];
        }
    }

    // Display other vector after swap
    std::cout << "\n\n\t\tOther vector after swap:";
    if (otherVector.empty()) {
        std::cout << "\n\t\t\t[Empty]";
    }
    else {
        for (size_t i = 0; i < otherVector.size(); ++i) {
            std::cout << "\n\t\t\t[" << i << "] " << otherVector[i];
        }
    }
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
* Precondition: input.dat file exists and contains valid student data in format: Name,GradeLevel,GPA
* Postcondition: Student elements from file are added to vector using push_back
*/
void VectorContainerApp::readFromFile() {
    std::ifstream file("input.dat");
    if (!file) {
        std::cout << "\n\t\tERROR: Could not open input.dat file.";
        std::cout << "\n\t\tMake sure input.dat is in the same directory as the executable.";
        return;
    }

    int count = 0;
    std::string line;

    while (std::getline(file, line)) {
        // Parse each line: Name,GradeLevel,GPA
        size_t firstComma = line.find(',');
        size_t secondComma = line.find(',', firstComma + 1);

        if (firstComma != std::string::npos && secondComma != std::string::npos) {
            std::string name = line.substr(0, firstComma);
            std::string gradeLevel = line.substr(firstComma + 1, secondComma - firstComma - 1);
            std::string gpaStr = line.substr(secondComma + 1);

            try {
                double gpa = std::stod(gpaStr);

                Student student;
                student.setName(name);
                student.setGradeLevel(gradeLevel);
                student.setGPA(gpa);

                m_Vector.push_back(student);
                count++;
            }
            catch (const std::exception& e) {
                std::cout << "\n\t\tWarning: Could not parse GPA from line: " << line;
            }
        }
        else {
            std::cout << "\n\t\tWarning: Invalid format in line: " << line;
        }
    }

    file.close();

    if (count > 0) {
        std::cout << "\n\t\tSuccessfully read " << count << " students from input.dat";
    }
    else {
        std::cout << "\n\t\tNo valid student data found in input.dat";
    }
}

void VectorContainerApp::displayVector() const {
    std::cout << "\n\n\tCurrent Vector: ";
    if (m_Vector.empty()) {
        std::cout << "Empty";
    }
    else {
        std::cout << "\n";
        for (size_t i = 0; i < m_Vector.size(); ++i) {
            std::cout << "\t[" << i << "] " << m_Vector[i] << "\n";
        }
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