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
		std::cout << "\n\t\tB. Push (append) an element to the end of the list";
		std::cout << "\n\t\tC. insert_after(pos) - inserts an element after the given position";
		std::cout << "\n\t\tD. pop_front() - pops an element from the beginning of the list";
		std::cout << "\n\t\tE. Pop an element from the end of the list";
		std::cout << "\n\t\tF. remove(value) - removes all elements with the same value";
		std::cout << "\n\t\tG. remove_if(cond) - removes all elements that meet the condition";
		std::cout << "\n\t\tH. erase_after(pos) - erases (deletes) all the elements after the given position (not including current node)";
		std::cout << "\n\t\tI. Change an existing node with new student information";
		std::cout << "\n\t\tJ. front() - returns a reference to the element at the front of the list";
		std::cout << "\n\t\tK. begin() - returns an iterator to the element at the front of the list";
		std::cout << "\n\t\tL. Return a reference to the element at the end of the list";
		std::cout << "\n\t\tM. Display all elements using being() and end()";
		std::cout << "\n\t\tN. sort() - sorts the list";
		std::cout << "\n\t\tO. reverse() - reverses the list";
		std::cout << "\n\t\tP. resize(n) - resizes the list to contain n elements";
		std::cout << "\n\t\tQ. clear() - clears the list";
		std::cout << "\n\t" << std::string(110, 196);
		std::cout << "\n\t\tR. Read data file and push_back()";
		std::cout << "\n\t" << std::string(110, 196);
		std::cout << "\n\t\t0. Return";
		std::cout << "\n\t" << std::string(110, 205);

		HandleInput(Input::inputChar("\n\t\tOption: ", "ABCDEFGHIJKLMNOPQR0"));
	}
}

void SinglyListApp::Clean()
{
	m_List.clear();
	numOfNodes = 0;
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

		std::cout << "\n\t\tSuccessfully pushed the element to the front of the list.";
		break;

	case 'B': // push an element to the back
		// if empty list, push to the front of the list
		if (m_List.empty())
			m_List.push_front(this->getStudent());
		else
		{
			// move the iterator to the last node
			auto it = m_List.begin();
			advance(it, numOfNodes - 1);

			// insert the element
			m_List.insert_after(it, this->getStudent());
		}
		numOfNodes++;

		std::cout << "\n\t\tSuccessfully pushed (appended) the element to the back of the list.";
		break;

	case 'C': // insert_after
	{
		// check if empty list
		if (m_List.empty())
		{
			std::cout << "\n\t\tERROR Cannot insert after an element on an empty list.";
			break;
		}

		Student temp(this->getStudent());
		// get the position of the node/ iterator
		size_t pos = Input::inputInteger("\n\t\tEnter the node (position) to insert the element after: ", 0, numOfNodes - 1);

		// move the iterator to the node
		auto it = m_List.begin();
		advance(it, pos);

		// insert the element
		m_List.insert_after(it, temp);
		numOfNodes++;

		std::cout << "\n\t\tSuccessfuly inserted the element after position (" << pos << ").";
		break;
	}

	case 'D': // pop_front
		// check if empty list
		if (m_List.empty())
		{
			std::cout << "\n\t\tERROR: Cannot pop on an empty list.";
			break;
		}
		m_List.pop_front();
		numOfNodes--;
		std::cout << "\n\t\tSuccessfully popped (removed) a element from the front.";
		break;

	case 'E': // pop an element at the back
		// check if empty list
		if (m_List.empty())
		{
			std::cout << "\n\t\tERROR: Cannot pop from an empty list.";
			break;
		}

		// one element in list
		if (numOfNodes == 1)
			m_List.pop_front();
		else
		{
			// move iterator to the 2nd to last node
			auto it = m_List.begin();
			advance(it, numOfNodes - 2);

			// pop (erase) the last element
			m_List.erase_after(it);
		}
		numOfNodes--;
		std::cout << "\n\t\tSuccessfully popped (removed) a element from the back.";
		break;

	case 'F': // remove
	{
		// check if list is empty
		if (m_List.empty())
		{
			std::cout << "\n\t\tERROR: Cannot remove from an empty list.";
			break;
		}

		size_t sizeBefore = numOfNodes;

		// get the details of the student to remove
		std::cout << "\n\t\tEnter the details of the element to remove:";
		Student temp = this->getStudent();

		// remove the student
		m_List.remove(temp);

		// recalculate the number of nodes
		numOfNodes = std::distance(m_List.begin(), m_List.end());
		size_t removedElements = sizeBefore - numOfNodes;
		if (removedElements != 0)
			std::cout << "\n\t\tSuccessfully removed " << removedElements << " elements from the list.";
		else
			std::cout << "\n\t\tNo elements were found and removed.";
		break;
	}

	case 'G': // remove_if()
	{
		size_t sizeBefore = numOfNodes;
		// get the name of the student to remove
		std::string name = Input::inputString("\n\t\tEnter the name of the student to remove: ", true);
		
		// remove any student with the same name
		m_List.remove_if([&](Student temp) 
		{
			return name == temp.Student::getName(); 
		});

		// recalculate the number of nodes
		numOfNodes = std::distance(m_List.begin(), m_List.end());
		size_t removedElements = sizeBefore - numOfNodes;
		if (removedElements != 0)
			std::cout << "\n\t\tSuccessfully removed " << removedElements << " elements from the list.";
		else
			std::cout << "\n\t\tNo elements were found and removed.";
		break;
	}

	case 'H': // erase_after
	{
		// check if list is empty
		if (m_List.empty())
		{
			std::cout << "\n\t\tERROR: Cannot erase from an empty list.";
			break;
		}

		size_t sizeBefore = numOfNodes;
		size_t pos = Input::inputInteger("\n\t\tEnter the node (position) to delete elements after: ", 0, numOfNodes - 1);

		// erase the students after the position
		auto it = m_List.begin();
		advance(it, pos);
		m_List.erase_after(it);

		// recalculate the number of nodes
		numOfNodes = std::distance(m_List.begin(), m_List.end());

		size_t removedElements = sizeBefore - numOfNodes;
		if (removedElements != 0)
			std::cout << "\n\t\tSuccessfully erased " << removedElements << " elements from the list.";
		else
			std::cout << "\n\t\tNo instances of the element were found and removed.";
		break;
	}

	case 'I': // change an existing node with new information
	{
		// ask for the position of th node to change
		size_t pos = Input::inputInteger("\n\t\tEnter the node (position) of the element to change: ", 0, numOfNodes - 1);

		// advance the iterator to the position
		auto it = m_List.begin();
		advance(it, pos);
		std::cout << "\n\tCurrent Student Information: " << *it;

		// get the new student information
		Student temp = this->getStudent();
		std::cout << "\n\tNew Student Information: " << temp;

		// ask if the user wants to commit their changes
		char commit = Input::inputChar("\n\n\t\tDo you want to commit the changes: ", "YN");
		if (commit == 'Y')
		{
			// reinitialize the node with new information
			*it = temp;
			std::cout << "\n\t\tSuccessfully changed the node at position (" << pos << ")";
		}
		else
			std::cout << "\n\t\tNo changes were made to the node at position (" << pos << ")";
		break;
	}

	case 'J': // front()
		if (m_List.empty())
		{
			std::cout << "\n\t\tERROR: Cannot retrieve the front of an empty list.";
			break;
		}

		std::cout << "\n\t\tFirst element from the list: " << m_List.front();
		break;

	case 'K': // begin()
		std::cout << "\n\t\tIterator to the first element: " << &m_List.front() << " " << m_List.front();
		break;

	case 'L': // reference to the last element of the list
	{
		if (m_List.empty())
		{
			std::cout << "\n\t\tERROR: Cannot retrieve the last element of an empty list.";
			break;
		}

		// traverse to the last node of the list
		auto it = m_List.begin();
		advance(it, numOfNodes - 1);

		std::cout << "\n\t\tLast element from the list: " << *it;
		break;
	}

	case 'M': // display all elements
	{
		// check if empty list
		if (m_List.empty())
		{
			std::cout << "\n\t\tERROR: Cannot display elements from an empty list.";
			break;
		}

		// display the elements by traversing using begin() and end()
		std::cout << "\n\t\tUsing begin() and end(), the list contains: ";
		for (auto it = m_List.begin(); it != m_List.end(); it++)
			std::cout << "\n\t\t\t" << &(*it) << " " << *it;
		break;
	}

	case 'N': // sort()
		// sort the list
		m_List.sort();

		// display the sorted list
		std::cout << "\n\t\tSorted List: ";
		for (auto it = m_List.begin(); it != m_List.end(); it++)
			std::cout << "\n\t\t\t" << &(*it) << " " << *it;
		break;
		
	case 'O': // reverse()
		// reverse the list
		m_List.reverse();

		// display the reversed list
		std::cout << "\n\t\tReversed List: ";
		for (auto it = m_List.begin(); it != m_List.end(); it++)
			std::cout << "\n\t\t\t" << &(*it) << " " << *it;
		break;

	case 'P': // resize()
	{
		// ask for the new size of the list
		size_t size = Input::inputInteger("\n\t\tEnter the new size of the list: ", true);

		// resize the array
		m_List.resize(size, Student());

		// recalculate the number of nodes in the list.
		numOfNodes = std::distance(m_List.begin(), m_List.end());
		std::cout << "\n\t\tSuccessfully resized the array to have " << size << " elements.";
		break;
	}

	case 'Q': // clear
		this->Clean();
		std::cout << "\n\t\tSuccessfully cleared the list of elements.";
		break;
		
	case 'R': // read file and push_back()
		break;

	case '0':
		m_MenuState = MenuState::Exited;
		return;

	}
	std::cout << "\n";
	std::system("pause");
}

Student SinglyListApp::getStudent() const
{
	char name[51] = "na";
	char level[2] = "0";

	// get student info
	strncpy_s(name, (Input::inputString("\n\t\tEnter a new student name: ", true)).c_str(), 51);
	strncpy_s(level, (Input::inputString("\t\tEnter their grade level (1-Freshman, 2-Sophmore, 3-Junior, or 4-Senior): ", "1234")).c_str(), 2);
	float gpa = Input::inputDouble("\t\tEnter their gpa (0.0...4.0): ", 0.0, 4.0);

	// set the student
	Student temp;
	temp.setName(name);
	temp.setGradeLevel(level);
	temp.setGPA(gpa);

	return temp;
}