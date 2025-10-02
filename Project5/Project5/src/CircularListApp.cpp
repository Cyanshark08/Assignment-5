#include "CircularListApp.h"
#include "Input.h"
#include <iomanip>

CircularListApp::CircularListApp()
	: m_MenuState(MenuState::Selection)
{
}

void CircularListApp::Run()
{
	while (m_MenuState != MenuState::Exited)
	{
		std::system("cls");
		
		std::cout << "\n\tCircular Lists are sequence containers that allow constant time insert and erase operations anywhere within the";
		std::cout << "\n\tsequence, iteration in both directions, and looping.";
		std::cout << "\n\n\t2. Circularly Linked List Container";
		std::cout << "\n\t" << std::string(110, 205);
		puts("\n\tA > clear() - Destroys all elements from the list");
		puts("\tB > resize(n) - Changes the list so that it contains n elements");
		puts("\tC > Read input.dat and push_front(e) - Adds a new element at the front of the list");
		puts("\tD > pop_front() - Deletes the first element");
		puts("\tE > front() - Accesses the first element");
		puts("\tF > Read input.dat and push_back(e) - Adds a new element at the end of the list");
		puts("\tG > pop_back() - Delete the last element");
		puts("\tH > back() Accesses the last element");
		puts("\tI > begin() - Returns an iterator refereing to the first element in the list");
		puts("\tJ > end() Returns an iterator referring to the past - the - end element in the list");
		puts("\tK > Using iterator begin() and end() returns all elements in the list");
		puts("\tL > rbegin() - Returns a reverse iterator pointing to the last element in the list");
		puts("\tM > rend() - Returns a reverse iterator pointing to the element preceding the first element");
		puts("\tin the list");
		puts("\tN > Using iterator rbegin() and rend() returns all elements in the list");
		puts("\tO > erase(it) - Removes from the vector a single element(using an iterator)");
		puts("\tP > erase(start_it, end_it) - Removes from the vector a range of elements(using iterators)");
		puts("\tQ > insert(it, entry) - Insert a new entry at the iterator.");
		puts("\tR > swap() - Exchanges the content of the container by another list's content of the same type");
		puts("\tS > Sort - Sorts the list.");
		std::cout << "\n\t" << std::string(110, 196);
		std::cout << "\n\t\t0. Return";
		std::cout << "\n\t" << std::string(110, 205);

		HandleInput(Input::inputChar("\n\t\tOption: ", "ABCDEFGHIJKLMNOPQR0"));

		std::system("pause");
	}
}

void CircularListApp::Clean()
{
	m_List.Clear();
	m_MenuState = MenuState::Exited;
}

void CircularListApp::Restart()
{
}

Student CircularListApp::getStudent() const
{
	return { Input::inputString("", true), Input::inputString("", true), Input::inputDouble("", 0.0, 4.0) };
}

void CircularListApp::HandleInput(char p_Input)
{
	switch (p_Input)
	{
	case 'A':
		m_List.Clear();
		break;
	case 'B':
		m_List.Resize(Input::inputInteger("\n\tEnter the new Size(1..100)", 1, 100));
		break;
	case 'C':
		m_List.PushFileFront("Input.dat");
		break;
	case 'D':
		try
		{
			m_List.PopFront();
		}
		catch (const ExceptionInterface& e)
		{
			printf("%s", e.Message().c_str());
			break;
		}
		break;
	case 'E':
		try
		{
			std::cout << "\n\tFront (first) Element: " << m_List.Front() << "\n\t";
		}
		catch (const ExceptionInterface& e)
		{
			printf("%s", e.Message().c_str());
			break;
		}
		break;
	case 'F':
		try
		{
			m_List.PushFileBack("Input.dat");
		}
		catch (const ExceptionInterface& e)
		{
			printf("%s", e.Message().c_str());
			break;
		}
		break;
	case 'G':
		try
		{
			m_List.PopBack();
		}
		catch (const ExceptionInterface& e)
		{
			printf("%s", e.Message().c_str());
			break;
		}
		break;
	case 'H':
		try
		{
			std::cout << "\n\tBack (last) Element: " << m_List.Back() << "\n\t";
		}
		catch (const ExceptionInterface& e)
		{
			printf("%s", e.Message().c_str());
			break;
		}
		break;
	case 'I':
		try
		{
			std::cout << "\n\tThe iterator referring to the first element: " << std::hex << &*m_List.begin() << "(" << &*m_List.begin() << ")\n\t";
		}
		catch (const ExceptionInterface& e)
		{
			printf("%s", e.Message().c_str());
			break;
		}
		break;
	case 'J':
		try
		{
			std::cout << "\n\tThe iterator referring to the past-the-end element: " << std::hex << &*m_List.end() << "\n\t";
		}
		catch (const ExceptionInterface& e)
		{
			printf("%s", e.Message().c_str());
			break;
		}
		break;
	case 'K':
		for (const auto& ele : m_List)
			std::cout << "\n\t" << ele << "\n\t";
		break;
	case 'L':
		std::cout << "\n\tThe iterator referring to the reverse first element: " << std::hex << &*m_List.rbegin() << "(" << &*m_List.rbegin() << ")\n\t";
		break;
	case 'M':
		std::cout << "\n\tThe iterator referring to the past-the-end element: " << std::hex << &*m_List.rend() << "\n\t";
		break;
	case 'N':
		for(auto i = m_List.rbegin(); i != m_List.rend(); i++)
			std::cout << "\n\t" << *i << "\n\t";
		break;
	case 'O':
		try
		{
			m_List.DeleteAt(m_List.begin());
		}
		catch (const ExceptionInterface& e)
		{
			printf("%s", e.Message().c_str());
			break;
		}
		break;
	case 'P':
		try
		{
			m_List.DeleteRange(m_List.begin(), m_List.end());
		}
		catch (const ExceptionInterface& e)
		{
			printf("%s", e.Message().c_str());
			break;
		}
		break;
	case 'Q':
		m_List.Insert(getStudent(), 0);
		break;
	case 'R':
	{
		CircularLinkedList temp;
		m_List.Swap(temp);
		break;
	}
	case 'S':
		m_List.Sort();
		break;
	case '0':
		break;
	}
}
