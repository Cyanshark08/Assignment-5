#include "Application.h"
#include <string>
#include "Input.h"

Application::Application()
	: m_State(MainAppState::MainApp),
	m_CurrentSubApp(AppID::InvalidApp)
{}

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
			}

			m_State = MainAppState::MainApp;
			m_CurrentSubApp = AppID::InvalidApp;
			break;
		}
	}
}

void Application::Clean()
{

}

void Application::DisplayMainMenu()
{
	puts("\n\tCMPR131 Chapter 5: Vector and List Container by ___ (1/6/21)");
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
