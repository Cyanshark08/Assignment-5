#include "SinglyListApp.h"
#include "Input.h"

SinglyListApp::SinglyListApp()
{
	m_MenuState = MenuState::Selection;
}

void SinglyListApp::Run()
{
	while (m_MenuState != MenuState::Exited)
	{
		std::system("cls");

		// display menu
		std::cout << "\n\tLists are sequence containers that allow constant time insert and erase operations anywhere within the";
		std::cout << "\n\tsequence, and iteration in both directions.";
		std::cout << "\n\n\t2. Singly Linked List Container";
		std::cout << "\n\t" << std::string(110, 205);
		std::cout << "\n\t\tA. push_front(entry) - pushes an element at the beginning of the list";
		std::cout << "\n\t\tB. push (append) an element at the end of the list";
		std::cout << "\n\t\tC. insert_after(pos) - inserts an element after the given position";
		std::cout << "\n\t\tD. pop_front() - pops an element from the beginning of the list";
		std::cout << "\n\t\tE. pop an element from the end of the list";
		std::cout << "\n\t\tF. remove(value) - removes all elements with the same value";
		std::cout << "\n\t\tG. remove_if(cond) - removes all elements that meet the condition";
		std::cout << "\n\t\tH. erase_after(pos) - erases (deletes) all the elements after the given position (not including current node)";
		std::cout << "\n\t\tI. front() - returns a reference to the element at the front of the list";
		std::cout << "\n\t\tJ. begin() - returns an iterator to the element at the front of the list";
		std::cout << "\n\t\tK. Return a reference to the element at the end of the list";
		std::cout << "\n\t\tL. end() - returns an iterator to the element at the end of the list";
		std::cout << "\n\t\tM. Display all elements using being() and end()";
		std::cout << "\n\t\tN. sort() - sorts the list";
		std::cout << "\n\t\tO. reverse() - reverses the list";
		std::cout << "\n\t\tP. resize(n) - resizes the list to contain n elements";
		std::cout << "\n\t\tQ. clear() - clears the list";
		std::cout << "\n\t" << std::string(110, 196);
		std::cout << "\n\t\tR. move iterator forward";
		std::cout << "\n\t\tS. move iterator backward";
		std::cout << "\n\t\tT. reset the iterator with begin()";
		std::cout << "\n\t\tU. read file and push_back()";
		std::cout << "\n\t" << std::string(110, 196);
		std::cout << "\n\t\t" << "0. Return";
		std::cout << "\n\t" << std::string(110, 205);

		HandleInput(Input::inputChar("\n\t\tOption: ", "ABCDEFGHIJKLMNOPQRSTU0"));
	}
}

void SinglyListApp::Clean()
{
	m_List.clear();
	m_MenuState = MenuState::Exited;
}

void SinglyListApp::Restart()
{
	this->Clean();
}

void SinglyListApp::HandleInput(char p_Input)
{
	switch (p_Input)
	{
	case 'A': // push_front
		// push the student to the front
		m_List.push_front(this->getStudent());
		break;

	case 'B': // push_back
		// empty list
		if (m_List.empty())
			m_List.push_front(this->getStudent());
		else
		{
			auto it = m_List.begin();

			// iterate until the iterator is one before the end
			while (next(it) != m_List.end())
				it++;

			// insert the element at the iterator's position
			m_List.insert_after(it, this->getStudent());
		}
		break;
		
	case 'C': // insert_after

	}

}

Student SinglyListApp::getStudent() const
{
	char name[51] = "na";
	char level[2] = "0";

	// get student info
	strncpy_s(name, (Input::inputString("\n\tEnter a new student name: ", true)).c_str(), 51);
	strncpy_s(level, (Input::inputString("\tEnter their grade level (1-Freshman, 2-Sophmore, 3-Junior, or 4-Senior): ", "1234")).c_str(), 2);
	float gpa = Input::inputDouble("\n\tEnter their gpa (0.0...4.0): ", 0.0, 4.0);

	// set the student
	Student temp;
	temp.setName(name);
	temp.setGradeLevel(level);
	temp.setGPA(gpa);

	return temp;
}