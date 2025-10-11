#pragma once

#include "SubApp.h"
#include "Student.h"
#include "SinglyLinkedList.h"
#include <iostream>
#include <forward_list>

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
	SinglyLinkedList m_List;
};

