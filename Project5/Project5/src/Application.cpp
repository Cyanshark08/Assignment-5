#include "Application.h"
#include "VectorContainerApp.h"
#include "SinglyListApp.h"
#include "CircularListApp.h"
#include <string>
#include "Input.h"

/*
* Name: Your Name
* Date: Current Date
* Description: Main application controller for Chapter 5 Vector and List Container assignment
*              Handles the main menu navigation and manages sub-application states.
*/

Application::Application()
    : m_State(MainAppState::MainApp),
    m_CurrentSubApp(AppID::InvalidApp)
{
}

void Application::Run()
{
    while (m_State != MainAppState::Exited)
    {
        switch (m_State)
        {
        case MainAppState::MainApp:
            DisplayMainMenu();
            QueryState();
            break;
        case MainAppState::SubApp:
            switch (m_CurrentSubApp)
            {
            case AppID::VectorContainerApp:
            {
                VectorContainerApp vectorApp;
                vectorApp.Run();
                break;
            }
            case AppID::SinglyListApp:
            {
                SinglyListApp singlyListApp;
                singlyListApp.Run();
                break;
            }
            case AppID::DoublyListApp:
            {
                // DoublyListApp doublyListApp;
                // doublyListApp.Run();
                std::cout << "\n\tDoubly Linked List App - Not yet implemented";
                std::cout << "\n";
                std::system("pause");
                break;
            }
            case AppID::CircularListApp:
            {
                CircularListApp circularListApp;
                circularListApp.Run();
                break;
            }
            case AppID::VectorListExampleApp:
            {
                // VectorListExampleApp exampleApp;
                // exampleApp.Run();
                std::cout << "\n\tVector/List Example App - Not yet implemented";
                std::cout << "\n";
                std::system("pause");
                break;
            }
            case AppID::InvalidApp:
            default:
                std::cout << "\n\tERROR: Invalid application selected";
                std::cout << "\n";
                std::system("pause");
                break;
            }

            m_State = MainAppState::MainApp;
            m_CurrentSubApp = AppID::InvalidApp;
            break;
        }
    }
}

void Application::Clean()
{
    // Cleanup if needed
    std::cout << "\n\tApplication cleanup completed.";
}

void Application::DisplayMainMenu()
{
    puts("\n\tCMPR131 Chapter 5: Vector and List Container by Your Name (Current Date)");
    puts(std::string(110, 205).c_str());
    puts("\t1 > Vector Container");
    puts("\t2 > Single-Linked List Container");
    puts("\t3 > Doubly-Linked List Container");
    puts("\t4 > Circular-Linked List Container");
    puts("\t5 > Application using Vector and/or List Container");
    puts(std::string(110, 196).c_str());
    puts("\t0. Exit");
    puts(std::string(110, 205).c_str());
}

void Application::QueryState()
{
    char choice = Input::inputChar("\n\tOption: ", "123450");
    switch (choice)
    {
    case '1':
        m_State = MainAppState::SubApp;
        m_CurrentSubApp = AppID::VectorContainerApp;
        break;
    case '2':
        m_State = MainAppState::SubApp;
        m_CurrentSubApp = AppID::SinglyListApp;
        break;
    case '3':
        m_State = MainAppState::SubApp;
        m_CurrentSubApp = AppID::DoublyListApp;
        break;
    case '4':
        m_State = MainAppState::SubApp;
        m_CurrentSubApp = AppID::CircularListApp;
        break;
    case '5':
        m_State = MainAppState::SubApp;
        m_CurrentSubApp = AppID::VectorListExampleApp;
        break;
    case '0':
        m_State = MainAppState::Exited;
        break;
    }
}