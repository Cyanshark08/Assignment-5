#include "SinglyListApp.h"
#include "Input.h"
#include <iterator>


SinglyListApp::SinglyListApp()
{
	m_MenuState = MenuState::Selection;
	numOfNodes = 0;
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
		std::cout << "\n\t\tB. push (append) an element to the end of the list";
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
		numOfNodes++;

		std::cout << "\n\tSuccessfully pushed the student to the front of the list.";
		break;

	case 'B': // push an element to the back
		// empty list
		if (m_List.empty())
			m_List.push_front(this->getStudent());
		else
		{
			auto it = m_List.begin();
			// move the iterator to the last node
			advance(it, numOfNodes - 1);

			// insert the element
			m_List.insert_after(it, this->getStudent());
		}
		numOfNodes++;

		std::cout << "\n\tSuccessfully pushed (appended) the student to the back of the list.";
		break;

	case 'C': // insert_after
	{
		if (m_List.empty())
		{
			std::cout << "\n\tERROR Cannot use 'insert_after' on an empty list.";
			break;
		}

		Student temp(this->getStudent());
		// get the position of the node/ iterator
		size_t pos = Input::inputInteger("\n\tEnter the node (position) to insert the student after: ", 0, numOfNodes - 1);

		// move the iterator to the node
		auto it = m_List.begin();
		advance(it, pos);

		// insert the element
		m_List.insert_after(it, temp);
		numOfNodes++;

		std::cout << "\n\tSuccessfuly inserted the student after position (" << pos << ").";
		break;
	}

	case 'D': // pop_front
		if (m_List.empty())
		{
			std::cout << "\n\tERROR: Cannot pop on an empty list.";
			break;
		}
		m_List.pop_front();
		numOfNodes--;
		std::cout << "\n\tSuccessfully popped (removed) a student from the front.";
		break;

	case 'E': // pop an element at the back
		if (m_List.empty())
		{
			std::cout << "\n\tERROR: Cannot pop from an empty list.";
			break;
		}

		// one element in list
		if (numOfNodes == 1)
			m_List.pop_front();
		else
		{
			auto it = m_List.begin();
			// move iterator to the 2nd to last node
			advance(it, numOfNodes - 2);

			// pop (erase) the element
			m_List.erase_after(it);
		}
		numOfNodes--;
		std::cout << "\n\tSuccessfully popped (removed) a student from the back.";
		break;

	case 'F': // remove
	{
		if (m_List.empty())
		{
			std::cout << "\n\tERROR: Cannot remove from an empty list.";
			break;
		}
		size_t sizeBefore = numOfNodes;

		std::cout << "\n\tEnter the details of the student to remove:";
		Student temp = this->getStudent();

		// remove the student
		m_List.remove(temp);

		// recalculate the number of nodes
		numOfNodes = distance(m_List.begin(), m_List.end());

		size_t removedElements = sizeBefore - numOfNodes;
		if (removedElements != 0)
			std::cout << "\n\tSuccessfully removed " << removedElements << " from the list.";
		else
			std::cout << "\n\tNo instances of the student were removed.";
		break;
	}

	case 'G': // remove_if
	{
		// display submenu

		break;
	}

	case 'H': // erase_after
	{
		if (m_List.empty())
		{
			std::cout << "\n\tERROR: Cannot erase from an empty list.";
			break;
		}

		size_t sizeBefore = numOfNodes;
		size_t pos = Input::inputInteger("\n\tEnter the node (position) to delete elements after: ", 0, numOfNodes - 1);

		// erase the students
		auto it = m_List.begin();
		advance(it, pos);
		m_List.erase_after(it);

		// recalculate the number of nodes
		numOfNodes = distance(m_List.begin(), m_List.end());

		size_t removedElements = sizeBefore - numOfNodes;
		if (removedElements != 0)
			std::cout << "\n\tSuccessfully erased " << removedElements << " from the list.";
		else
			std::cout << "\n\tNo instances of the student were removed.";
		break;
	}

	case 'I':
		break;

		std::system("pause");
	}
}

Student SinglyListApp::getStudent() const
{
	char name[51] = "na";
	char level[2] = "0";

	// get student info
	strncpy_s(name, (Input::inputString("\n\tEnter a new student name: ", true)).c_str(), 51);
	strncpy_s(level, (Input::inputString("\tEnter their grade level (1-Freshman, 2-Sophmore, 3-Junior, or 4-Senior): ", "1234")).c_str(), 2);
	float gpa = Input::inputDouble("\tEnter their gpa (0.0...4.0): ", 0.0, 4.0);

	// set the student
	Student temp;
	temp.setName(name);
	temp.setGradeLevel(level);
	temp.setGPA(gpa);

	return temp;
}