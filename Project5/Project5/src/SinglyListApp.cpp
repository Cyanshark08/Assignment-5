#include "SinglyListApp.h"
#include "Input.h"
#include <iterator>
#include <sstream>
#include <fstream>


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
		std::cout << "\n\t\tG. remove_if(condition) - removes all elements based on a condition";
		std::cout << "\n\t\tH. erase_after(pos) - erases (deletes) the element after the given position";
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
		// check if empty list
		if (m_List.empty())
		{
			std::cout << "\n\t\tERROR: Cannot remove from an empty list.";
			break;
		}

		do
		{
			size_t sizeBefore = numOfNodes;
			std::system("cls");
			// display the submenu
			std::cout << "\n\tG. Remove_if(condition) Submenu";
			std::cout << "\n\t" << std::string(110, 205);
			std::cout << "\n\t\tA. Remove by name";
			std::cout << "\n\t\tB. Remove by grade level";
			std::cout << "\n\t\tC. Remove students below a certain GPA";
			std::cout << "\n\t\tD. Display all students";
			std::cout << "\n\t" << std::string(110, 196);
			std::cout << "\n\t\t0. Return";
			std::cout << "\n\t" << std::string(110, 205);
			switch (Input::inputChar("\n\t\tOption: ", "ABCD0"))
			{
			case 'A': // remove by name
			{
				// get the name of the student to remove
				std::string name = Input::inputString("\n\t\tEnter the name of the student to remove: ", true);

				// remove any student with the same name
				m_List.remove_if([&](Student temp)
					{
						return name == temp.Student::getName();
					});
				break;
			}

			case 'B': // remove by grade level
			{
				// get the grade level of students to remove
				std::string levels[4] = { "Freshmen", "Sophmore", "Junior", "Senior" };
				int level = Input::inputInteger("\n\tEnter the grade level of the students to remove: ", 1, 4);

				// remove the students with the same grade level
				m_List.remove_if([&](Student temp)
					{
						return levels[level - 1] == temp.Student::getLevel();
					});
				break;
			}

			case 'C': // remove by GPA
			{
				// get the gpa
				double gpaThreshold = Input::inputDouble("\n\tEnter the GPA threshold to remove students below: ", 0.0, 4.0);
				// remove the students with the same grade level
				m_List.remove_if([&](Student temp)
					{
						return gpaThreshold > temp.Student::getGPA();
					});
				break;
			}

			case 'D': // display all students
				// display the elements by traversing using begin() and end()
				std::cout << "\n\t\tUsing begin() and end(), the list contains: ";
				for (auto it = m_List.begin(); it != m_List.end(); it++)
					std::cout << "\n\t\t\t" << &(*it) << " (" << *it << ")";
				break;

			case '0': return;
			}

			// recalculate the number of nodes
			numOfNodes = std::distance(m_List.begin(), m_List.end());
			size_t removedElements = sizeBefore - numOfNodes;
			if (removedElements != 0)
				std::cout << "\n\t\tSuccessfully removed " << removedElements << " elements from the list.";
			else
				std::cout << "\n\t\tNo elements were found and removed.";

			std::cout << "\n";
			std::system("pause");
		} while (true);
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
		size_t pos = Input::inputInteger("\n\t\tEnter the node (position) to delete the element after: ", 0, numOfNodes - 1);

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
		// check if empty list
		if (m_List.empty())
		{
			std::cout << "\n\t\tERROR: Cannot change nodes of an empty list.";
			break;
		}

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
		// check if empty list
		if (m_List.empty())
		{
			std::cout << "\n\t\tERROR: Cannot retrieve the front of an empty list.";
			break;
		}

		std::cout << "\n\t\tFirst element from the list: " << m_List.front();
		break;

	case 'K': // begin()
		// check if empty list
		if (m_List.empty())
		{
			std::cout << "\n\t\tERROR: Cannot return iterator to first element from an empty list.";
			break;
		}
		std::cout << "\n\t\tIterator to the first element: " << &m_List.front() << " (" << m_List.front() << ")";
		break;

	case 'L': // reference to the last element of the list
	{
		// check if empty list
		if (m_List.empty())
		{
			std::cout << "\n\t\tERROR: Cannot retrieve the last element of an empty list.";
			break;
		}

		// traverse to the last node of the list
		auto it = m_List.begin();
		advance(it, numOfNodes - 1);

		std::cout << "\n\t\tLast element from the list: " << &(*it) << " (" << *it << ")";
		std::cout << "\n";
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
			std::cout << "\n\t\t\t" << &(*it) << " (" << *it << ")";
		break;
	}

	case 'N': // sort()
		// sort the list
		m_List.sort();

		// check if empty list
		if (m_List.empty())
		{
			std::cout << "\n\t\tSorted the empty list.";
			break;
		}

		// display the sorted list
		std::cout << "\n\t\tSorted List: ";
		for (auto it = m_List.begin(); it != m_List.end(); it++)
			std::cout << "\n\t\t\t" << &(*it) << " (" << *it << ")";
		break;

	case 'O': // reverse()
		// reverse the list
		m_List.reverse();

		// check if empty list
		if (m_List.empty())
		{
			std::cout << "\n\t\tReversed the empty list.";
			break;
		}

		// display the reversed list
		std::cout << "\n\t\tReversed List: ";
		for (auto it = m_List.begin(); it != m_List.end(); it++)
			std::cout << "\n\t\t\t" << &(*it) << " (" << *it << ")";
		break;

	case 'P': // resize()
	{
		// ask for the new size of the list
		size_t size = Input::inputInteger("\n\t\tEnter the new size of the list: ", true);

		// resize the array
		m_List.resize(size, Student());

		// recalculate the number of nodes in the list.
		numOfNodes = std::distance(m_List.begin(), m_List.end());
		std::cout << "\n\t\tSuccessfully resized the list to have " << size << " default elements.";
		break;
	}

	case 'Q': // clear
		m_List.clear();
		std::cout << "\n\t\tSuccessfully cleared the list of elements.";
		break;

	case 'R': // read file and push_back()
	{
		// get the file name
		std::string fileName = Input::inputString("\n\tEnter the file name: ", false);
		std::fstream file;

		// open the file to read
		file.open(fileName, std::ios::in);

		// check if successful open
		if (!file)
		{
			std::cout << "\n\tERROR: Could not open file.";
			break;
		}
		// advance the iterator the the last node
		auto it = m_List.before_begin();
		if (!m_List.empty())
			advance(it, numOfNodes - 1);

		// read the file
		std::string line;
		while (std::getline(file, line, '\n'))
		{
			std::istringstream tokens(line);
			std::string name, level, gpa;
			Student temp;

			// retrieve the data
			std::getline(tokens, name, ',');
			std::getline(tokens, level, ',');
			std::getline(tokens, gpa);

			// set temp
			temp.setName(name);
			temp.setGradeLevel(level);
			temp.setGPA(std::stod(gpa));

			// push to the back of the list
			if (m_List.empty())
			{
				m_List.push_front(temp);
				it = m_List.begin();
			}
			else
			{
				m_List.insert_after(it, temp);
				it++;
			}
			numOfNodes++;
		}

		// close the file
		file.close();
		std::cout << "\n\tSuccessfully loaded students from file.";
		break;
	}

	case '0': // return
		this->Restart();
		return;
	}
	std::cout << "\n";
	std::system("pause");
}

Student SinglyListApp::getStudent() const
{
	// get student info
	std::string name = Input::inputString("\n\t\tEnter a new student name: ", true);
	int level = Input::inputInteger("\t\tEnter their grade level (1-Freshman, 2-Sophmore, 3-Junior, or 4-Senior): ", 1, 4);
	double gpa = Input::inputDouble("\t\tEnter their gpa (0.0...4.0): ", 0.0, 4.0);

	// set the student
	std::string levels[4] = { "Freshmen", "Sophmore", "Junior", "Senior" };

	Student temp;
	temp.setName(name);
	temp.setGradeLevel(levels[level - 1]);
	temp.setGPA(gpa);

	return temp;
}