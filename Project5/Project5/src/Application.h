#pragma once
#include "SubApp.h"

enum class MainAppState
{
	MainApp,
	SubApp,
	Exited
};

class Application
{
public:

	Application();

	/*
	* Precondition: None
	* 
	* Postcondition: Initializes main application loop; handles each SubApp
	*/
	void Run();

	/*
	* Precondition: None
	*
	* Postcondition: Cleans all SubApps
	*/
	void Clean();

private:
	void DisplayMainMenu();
	void QueryState();

private:
	MainAppState m_State;
	AppID m_CurrentSubApp;

};

