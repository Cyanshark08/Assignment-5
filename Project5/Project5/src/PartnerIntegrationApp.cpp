#include "PartnerIntegrationApp.h"
#include <iostream>
#include <limits>

/*
* Name: [Your Name] & [Partner's Name]
* Date: [Current Date]
* Description: Implementation of integrated partner's code using group's Student class
*              Provides menu interface to partner's vector and list handlers
*/

PartnerIntegrationApp::PartnerIntegrationApp()
    : SubApp(AppID::VectorListExampleApp),
    m_MenuState(MenuState::ContainerChoice),
    m_CurrentContainerType("None") {
}

void PartnerIntegrationApp::Run() {
    while (m_MenuState != MenuState::Exited) {
        std::system("cls");

        if (m_MenuState == MenuState::ContainerChoice) {
            std::cout << "\n\tCMPR131 Chapter 5: Partner's Integrated Application";
            std::cout << "\n\t" << std::string(70, 205);
            std::cout << "\n\tChoose container type:";
            std::cout << "\n\t1> Vector Container (Partner's Implementation)";
            std::cout << "\n\t2> List Container (Partner's Implementation)";
            std::cout << "\n\t" << std::string(70, 196);
            std::cout << "\n\t0> Return to Main Menu";
            std::cout << "\n\t" << std::string(70, 205);

            char choice = Input::inputChar("\n\tOption: ", "120");
            switch (choice) {
            case '1':
                m_Handler = std::make_unique<vectorHandler>();
                m_CurrentContainerType = "VECTOR";
                m_MenuState = MenuState::Selection;
                m_Handler->loadFromFile("input.dat");
                break;
            case '2':
                m_Handler = std::make_unique<listHandler>();
                m_CurrentContainerType = "LIST";
                m_MenuState = MenuState::Selection;
                m_Handler->loadFromFile("input.dat");
                break;
            case '0':
                m_MenuState = MenuState::Exited;
                return;
            }
        }
        else if (m_MenuState == MenuState::Selection) {
            std::cout << "\n\tPartner's Integrated Application";
            std::cout << "\n\tContainer: " << m_CurrentContainerType;
            std::cout << "\n\t" << std::string(70, 205);
            std::cout << "\n\t1> Add a student";
            std::cout << "\n\t2> Delete a student";
            std::cout << "\n\t3> Display all students";
            std::cout << "\n\t4> Display student frequencies";
            std::cout << "\n\t" << std::string(70, 196);
            std::cout << "\n\t5> Switch container type";
            std::cout << "\n\t0> Return to Main Menu";
            std::cout << "\n\t" << std::string(70, 205);

            char option = Input::inputChar("\n\tOption: ", "123450");
            HandleInput(option);
        }
    }
}

void PartnerIntegrationApp::HandleInput(char p_Input) {
    if (!m_Handler) {
        std::cout << "\n\tERROR: No container selected.";
        std::cout << "\n";
        std::system("pause");
        return;
    }

    switch (p_Input) {
    case '1':
        addStudent();
        break;
    case '2':
        deleteStudent();
        break;
    case '3':
        displayStudents();
        break;
    case '4':
        displayFrequencies();
        break;
    case '5':
        m_MenuState = MenuState::ContainerChoice;
        m_Handler.reset();
        break;
    case '0':
        m_MenuState = MenuState::Exited;
        break;
    }

    if (p_Input != '0' && p_Input != '5') {
        std::cout << "\n";
        std::system("pause");
    }
}

void PartnerIntegrationApp::addStudent() {
    /*
    * Precondition: Handler is initialized and user provides valid input
    * Postcondition: Student is added to the current container
    */
    Student s = getStudentFromInput();
    m_Handler->addStudent(s);
    std::cout << "\n\tStudent added to " << m_CurrentContainerType << " successfully.";
}

void PartnerIntegrationApp::deleteStudent() {
    /*
    * Precondition: Handler is initialized and user provides valid input
    * Postcondition: Student is removed from current container if found
    */
    Student s = getStudentFromInput();

    bool deleted = m_Handler->deleteStudent(s);

    if (deleted) {
        std::cout << "\n\tStudent deleted successfully from " << m_CurrentContainerType << ".";
    }
    else {
        std::cout << "\n\tERROR: Invalid input - student not found in " << m_CurrentContainerType << ".";
    }
}

void PartnerIntegrationApp::displayStudents() const {
    /*
    * Precondition: Handler is initialized
    * Postcondition: All students are displayed from current container
    */
    std::cout << "\n\tStudents in " << m_CurrentContainerType << ":\n";
    m_Handler->displayStudents();
}

void PartnerIntegrationApp::displayFrequencies() const {
    /*
    * Precondition: Handler is initialized
    * Postcondition: Frequency count of students is displayed
    */
    std::cout << "\n\tStudent frequencies in " << m_CurrentContainerType << ":\n";
    m_Handler->displayFrequencies();
}

std::string PartnerIntegrationApp::getStudentName(const std::string& prompt) const {
    /*
    * Precondition: Prompt string is provided
    * Postcondition: Returns validated student name
    */
    std::string name;
    bool valid = false;

    while (!valid) {
        name = Input::inputString(prompt, true);
        valid = !name.empty();

        for (char c : name) {
            if (!std::isalpha(c) && !std::isspace(c)) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            std::cout << "\tERROR: Name must contain only letters and spaces.\n";
        }
    }
    return name;
}

std::string PartnerIntegrationApp::getGradeLevel(const std::string& prompt) const {
    /*
    * Precondition: Prompt string is provided
    * Postcondition: Returns validated grade level
    */
    std::string grade;
    bool valid = false;

    while (!valid) {
        grade = Input::inputString(prompt, true);
        std::string lowerGrade = grade;
        std::transform(lowerGrade.begin(), lowerGrade.end(), lowerGrade.begin(), ::tolower);

        if (lowerGrade == "freshman" || lowerGrade == "sophomore" ||
            lowerGrade == "junior" || lowerGrade == "senior") {
            valid = true;
            grade = lowerGrade;
            grade[0] = std::toupper(grade[0]);
        }
        else {
            std::cout << "\tERROR: Must be 'freshman', 'sophomore', 'junior', or 'senior'.\n";
        }
    }
    return grade;
}

Student PartnerIntegrationApp::getStudentFromInput() const {
    /*
    * Precondition: None
    * Postcondition: Returns validated Student object
    */
    Student s;

    std::string name = getStudentName("\tEnter student name: ");
    std::string grade = getGradeLevel("\tEnter grade level (freshman/sophomore/junior/senior): ");
    double gpa = Input::inputDouble("\tEnter GPA (0.0-4.0): ", 0.0, 4.0);

    s.setName(name);
    s.setGradeLevel(grade);
    s.setGPA(gpa);

    return s;
}

void PartnerIntegrationApp::Clean() {
    /*
    * Precondition: Application may have allocated resources
    * Postcondition: All resources are cleaned up
    */
    m_Handler.reset();
    m_MenuState = MenuState::ContainerChoice;
    m_CurrentContainerType = "None";
}

void PartnerIntegrationApp::Restart() {
    /*
    * Precondition: Application may be in any state
    * Postcondition: Application is reset to initial state
    */
    Clean();
}