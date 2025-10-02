#pragma once
#include "SubApp.h"
#include "Student.h"
#include "Input.h"
#include "containerHandler.h"
#include "vectorHandler.h"
#include "listHandler.h"
#include <memory>
#include <iostream>
#include <algorithm>
#include <cctype>

/*
* Name: [Your Name] & [Partner's Name]
* Date: [Current Date]
* Description: Integration of partner's vector/list handler with group's Student class
*              Demonstrates STL containers with polymorphic handler pattern
*/

class PartnerIntegrationApp : public SubApp {
public:
    enum class MenuState {
        Exited,
        Selection,
        ContainerChoice
    };

    PartnerIntegrationApp();

    /*
    * Precondition: Application is initialized
    * Postcondition: Main application loop runs until user exits
    */
    void Run() override;

    /*
    * Precondition: Application may have allocated resources
    * Postcondition: All resources are cleaned up
    */
    void Clean() override;

    /*
    * Precondition: Application may be in any state
    * Postcondition: Application is reset to initial state
    */
    void Restart() override;

private:
    /*
    * Precondition: Valid character input is provided
    * Postcondition: Appropriate action is executed based on input
    */
    void HandleInput(char p_Input) override;

    /*
    * Precondition: None
    * Postcondition: Container handler is selected and initialized
    */
    void chooseContainer();

    /*
    * Precondition: None
    * Postcondition: New student is added to current container
    */
    void addStudent();

    /*
    * Precondition: None
    * Postcondition: Student is removed from current container if found
    */
    void deleteStudent();

    /*
    * Precondition: None
    * Postcondition: All students are displayed from current container
    */
    void displayStudents() const;

    /*
    * Precondition: None
    * Postcondition: Frequency count of students is displayed
    */
    void displayFrequencies() const;

    /*
    * Precondition: None
    * Postcondition: Returns a Student object with validated user input
    */
    Student getStudentFromInput() const;

private:
    MenuState m_MenuState;
    std::unique_ptr<containerHandler> m_Handler;
    std::string m_CurrentContainerType;
};