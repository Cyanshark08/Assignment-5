#pragma once

#include "SubApp.h"
#include "Student.h"
#include <iostream>

class SinglyListApp : public SubApp
{
public:

	enum class MenuState
	{
		Exited, 
		Selection
	};

	SinglyListApp();

	void Run() override;

	void Clean() override;

	void Restart() override;

private:
	void HandleInput(char p_Input) override;

private:
	MenuState m_MenuState;
};

