#pragma once
#include "CircularLinkedList.h"
#include "SubApp.h"
#include "Student.h"

class CircularListApp : public SubApp
{
public:

	enum class MenuState
	{
		Exited,
		Selection
	};

	CircularListApp();

	void Run() override;

	void Clean() override;

	void Restart() override;

	Student getStudent() const;

private:
	void HandleInput(char p_Input) override;

private:
	MenuState m_MenuState;
	circular_list m_List;
};

