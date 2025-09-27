#pragma once

#include "SubApp.h"
#include "Student.h"
#include <iostream>
#include <forward_list>
#include <iterator>

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

	Student getStudent() const;

private:
	void HandleInput(char p_Input) override;

private:
	MenuState m_MenuState;
	forward_list<Student> m_List;
};

