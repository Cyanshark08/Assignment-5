#include "SinglyListApp.h"
#include "Input.h"
#include <iterator>
#include <sstream>
#include <fstream>


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
		std::cout << "\n\t\tA. push_front(element) - pushes an element at the beginning of the list";
		std::cout << "\n\t\tB. push_back(element) - pushes an element at the end of the list";
		std::cout << "\n\t\tC. insert_after(pos) - inserts an element after the given position";
		std::cout << "\n\t\tD. pop_front() - pops an element from the beginning of the list";
		std::cout << "\n\t\tE. pop_back() - pops an element at the end of the list";
		std::cout << "\n\t\tF. remove(value) - removes all elements with the same value";
		std::cout << "\n\t\tG. remove_if(condition) - removes all elements based on a condition";
		std::cout << "\n\t\tH. erase_after(pos) - erases (deletes) the element after the given position";
		std::cout << "\n\t\tI. update_element(pos, element) - updates the current element with new data";
		std::cout << "\n\t\tJ. front() - returns a reference to the element at the front of the list";
		std::cout << "\n\t\tK. begin() - returns an iterator to the element at the front of the list";
		std::cout << "\n\t\tL. back() - returns a reference to the element at the back of the list";
		std::cout << "\n\t\tM. end() - returns an iterator referring to the past-the-end element";
		std::cout << "\n\t\tN. Display all elements using begin() and end()";
		std::cout << "\n\t\tO. sort() - sorts the list";
		std::cout << "\n\t\tP. reverse() - reverses the list";
		std::cout << "\n\t\tQ. resize(n) - resizes the list to contain n elements";
		std::cout << "\n\t\tR. clear() - clears the list";
		std::cout << "\n\t" << std::string(110, 196);
		std::cout << "\n\t\tS. push_from_file - read data file and push_back()";
		std::cout << "\n\t" << std::string(110, 196);
		std::cout << "\n\t\t0. Return";
		std::cout << "\n\t" << std::string(110, 205);

		HandleInput(Input::inputChar("\n\t\tOption: ", "ABCDEFGHIJKLMNOPQRS0"));
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
		m_List.push_front(this->getStudent());
		std::cout << "\n\t\tSuccessfully pushed the element to the front of the list.";
		break;
		
	case 'B': // push_back
		m_List.push_back(this->getStudent());
		std::cout << "\n\t\tSuccessfully pushed (appended) the element to the back of the list.";
		break;

	case 'C': // insert_after
		try
		{
			// check if empty list
			if (m_List.empty())
				throw SinglyLinkedList::E_NullList();

			// get the position of the node/ iterator
			size_t index = Input::inputInteger("\n\t\tEnter the index (position) to insert the element after: ", 0, m_List.getNumOfElements() - 1);
			if (index >= m_List.getNumOfElements())
				throw SinglyLinkedList::E_IndexOutOfBounds(index, m_List.getNumOfElements() - 1);

			// insert the student
			m_List.insert_after(index, this->getStudent());
			std::cout << "\n\t\tSuccessfully inserted the element after index (" << index << ").";
		}
		catch (const ExceptionInterface &e)
		{
			std::cout << e.Message();
			break;
		}
		break;

	case 'D': // pop_front
		try
		{
			m_List.pop_front();
		}
		catch (const ExceptionInterface &e)
		{
			std::cout << e.Message();
			break;
		}
		std::cout << "\n\t\tSuccessfully popped (removed) a element from the front.";
		break;

	case 'E': // pop_back
		try
		{
			m_List.pop_back();
		}
		catch (const ExceptionInterface &e)
		{
			std::cout << e.Message();
			break;
		}
		std::cout << "\n\t\tSuccessfully popped (removed) a element from the back.";
		break;

	case 'F': // remove
		try
		{
			if (m_List.empty())
				throw SinglyLinkedList::E_NullList();

			size_t removedElements = m_List.remove(this->getStudent());
			if (removedElements == 0)
				std::cout << "\n\t\tNo instance of student found and removed.";
			else
				std::cout << "\n\t\tSuccessfully removed " << removedElements << " from the list.";
		}
		catch (const ExceptionInterface &e)
		{
			std::cout << e.Message();
		}
		break;

	case 'G': // remove_if()
	{
		try
		{
			if (m_List.empty())
				throw SinglyLinkedList::E_NullList();
			do
			{
				int removedElements = 0;
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
					removedElements = m_List.remove_if(true, false, false, name, "", 0);

					if (removedElements == 0)
						std::cout << "\n\t\tNo instance of students were found and removed.";
					else
						std::cout << "\n\t\tSuccessfully removed " << removedElements << " elements from the list.";
					break;
				}

				case 'B': // remove by grade level
				{
					// get the grade level of students to remove
					std::string levels[4] = { "Freshmen", "Sophmore", "Junior", "Senior" };
					int level = Input::inputInteger("\n\tEnter the grade level of the students to remove (1-Freshman, 2-Sophmore, 3-Junior, or 4-Senior): ", 1, 4);
					removedElements = m_List.remove_if(false, true, false, "", levels[level - 1], 0);

					if (removedElements == 0)
						std::cout << "\n\t\tNo instance of students were found and removed.";
					else
						std::cout << "\n\t\tSuccessfully removed " << removedElements << " elements from the list.";
					break;
				}

				case 'C': // remove by GPA
				{
					// get the gpa threshold of the students to remove
					double gpaThreshold = Input::inputDouble("\n\tEnter the GPA threshold to remove students below: ", 0.0, 4.0);
					// remove the students with the same grade level
					removedElements = m_List.remove_if(false, false, true, "", "", gpaThreshold);

					if (removedElements == 0)
						std::cout << "\n\t\tNo instance of students were found and removed.";
					else
						std::cout << "\n\t\tSuccessfully removed " << removedElements << " elements from the list.";
					break;
				}

				case 'D': // display all students
					std::cout << "\n\t\tUsing begin() and end(), the list contains: " << m_List;
					break;

				case '0': return;
				}

				

				std::cout << "\n";
				std::system("pause");
			} while (true);
		}
		catch (const ExceptionInterface &e)
		{
			std::cout << e.Message();
			break;
		}
		break;
	}

	case 'H': // erase_after
		try
		{
			if (m_List.empty())
				throw SinglyLinkedList::E_NullList();

			// get the position of the index to erase after
			size_t index = Input::inputInteger("\n\t\tEnter the index (position) to delete the element after: ", 0, m_List.getNumOfElements() - 2);
			if (index > m_List.getNumOfElements() - 2)
				throw SinglyLinkedList::E_IndexOutOfBounds(index, m_List.getNumOfElements() - 1);

			m_List.erase_after(index);
			std::cout << "\n\t\tSuccessfully erased the student after index [" << index << "]";
		}
		catch (const ExceptionInterface &e)
		{
			std::cout << e.Message();
			break;
		}
		break;

	case 'I': // change an existing node with new information
		try
		{
			if (m_List.empty())
				throw SinglyLinkedList::E_NullList();

			// get the position of the node to update
			size_t index = Input::inputInteger("\n\t\tEnter the node (position) of the element to change: ", 0, m_List.getNumOfElements() - 1);
			if (index >= m_List.getNumOfElements() - 1)
				throw SinglyLinkedList::E_IndexOutOfBounds(index, m_List.getNumOfElements() - 1);

			Student temp = this->getStudent();
			std::cout << "\n\tNew Student Information: " << temp;

			// ask if the user wants to commit their changes
			char commit = Input::inputChar("\n\n\t\tDo you want to commit the changes: ", "YN");
			if (commit == 'Y')
			{
				// update the node
				m_List.update_element(index, temp);
				std::cout << "\n\t\tSuccessfully changed the node at position (" << index << ")";
			}
			else
				std::cout << "\n\t\tNo changes were made to the node at position (" << index << ")";
		}
		catch (const ExceptionInterface &e)
		{
			std::cout << e.Message();
			break;
		}
		break;

	case 'J': // front()
		try
		{
			std::cout << "\n\t\tFirst element in the list: " << m_List.front();
		}
		catch (const ExceptionInterface &e)
		{
			std::cout << e.Message();
			break;
		}
		break;

	case 'K': // begin()
		try
		{
			if (m_List.empty())
				throw SinglyLinkedList::E_NullList();

			auto it = m_List.begin();
			std::cout << "\n\t\tIterator pointing to the first element: " << &(*it) << " (" << *it << ")";;
		}
		catch (const ExceptionInterface &e)
		{
			std::cout << e.Message();
		}
		break;
		
	case 'L': // back
		try
		{
			std::cout << "\n\tLast element in the list: " << m_List.back();
		}
		catch (const ExceptionInterface &e)
		{
			std::cout << e.Message();
			break;
		}
		break;

	case 'M':
		try
		{
			if (m_List.empty())
				throw SinglyLinkedList::E_NullList();

			auto it = m_List.begin();
			std::cout << "\n\t\tIterator referring to the past-the-end element: " << &it;
		}
		catch (const ExceptionInterface &e)
		{
			std::cout << e.Message();
		}
		break;

	case 'N': // display all elements
	{
		// display the elements by traversing using begin() and end()
		std::cout << "\n\t\tUsing begin() and end(), the list contains: ";
		std::cout << m_List;
		break;
	}

	case 'O': // sort()
		m_List.sort();
		std::cout << "\n\t\tSorted List: " << m_List;
		break;

	case 'P': // reverse()
		m_List.reverse();
		std::cout << "\n\t\tReversed List: " << m_List;
		break;

	case 'Q': // resize()
	{
		// ask for the new size of the list
		size_t size = Input::inputInteger("\n\t\tEnter the new size of the list: ", true);
		m_List.resize(size);
		std::cout << "\n\t\tSuccessfully resized the list to have " << size << " default elements.";
		break;
	}

	case 'R': // clear
		m_List.clear();
		std::cout << "\n\t\tSuccessfully cleared the list of elements.";
		break;

	case 'S': // read file and push_back()
	{
		size_t sizeBefore = m_List.getNumOfElements();
		// get the file name
		std::string fileName = Input::inputString("\n\t\tEnter the file name: ", false);
		std::fstream file;

		// open the file to read
		file.open(fileName, std::ios::in);

		// check if successful open
		if (!file)
		{
			std::cout << "\n\tERROR: Could not open file.";
			break;
		}
		file.close();
		// read and push from the file
		m_List.push_from_file(fileName);

		std::cout << "\n\t\tSuccessfully read and pushed " << m_List.getNumOfElements() - sizeBefore << " elements into the list.";
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