#include "SinglyLinkedList.h"
#include <sstream>
#include <fstream>

SinglyLinkedList::SinglyLinkedList()
{
	m_NumOfElements = 0;
}

bool SinglyLinkedList::empty() const
{
	return m_List.empty();
}

int SinglyLinkedList::getNumOfElements() const
{
	return m_NumOfElements;
}
void SinglyLinkedList::push_front(Student m_Data)
{
	m_List.push_front(m_Data);
	m_NumOfElements++;
}

void SinglyLinkedList::push_back(Student m_Data)
{
	if (m_List.empty())
	{
		m_List.push_front(m_Data);
		m_NumOfElements++;
	}
	else
	{
		// move the iterator to the last node
		auto it = m_List.begin();
		advance(it, m_NumOfElements - 1);

		// insert the element
		m_List.insert_after(it, m_Data);
		m_NumOfElements++;
	}
}

void SinglyLinkedList::insert_after(size_t m_Index, Student m_Data)
{
	if (m_List.empty())
		throw E_NullList();
	if (m_Index >= m_NumOfElements)
		throw E_IndexOutOfBounds(m_Index, m_NumOfElements - 1);

	// advance the iterator to the given position (index)
	auto it = m_List.begin();
	advance(it, m_Index);

	// insert the element
	m_List.insert_after(it, m_Data);
	m_NumOfElements++;
}

void SinglyLinkedList::pop_front()
{
	if (m_List.empty())
		throw E_NullList();
	
	// pop the front element
	m_List.pop_front();
	m_NumOfElements--;
}

void SinglyLinkedList::pop_back()
{
	if (m_List.empty())
		throw E_NullList();

	if (m_NumOfElements == 1)
		m_List.pop_front();
	else
	{
		// advance the iterator the 2nd to last node
		auto it = m_List.begin();
		advance(it, m_NumOfElements - 2);

		// remove the element after the 2nd to last node
		m_List.erase_after(it);
	}
	m_NumOfElements--;
}

int SinglyLinkedList::remove(Student m_Data)
{
	if (m_List.empty())
		throw E_NullList();

	size_t sizeBefore = m_NumOfElements;
	m_List.remove(m_Data);
	// recalculate the number of elements
	m_NumOfElements = std::distance(m_List.begin(), m_List.end());

	// return the number of elements removed
	return sizeBefore - m_NumOfElements;
}

int SinglyLinkedList::remove_if(bool matchName, bool matchLevel, bool matchGpa, 
	std::string nameToSearch, std::string levelToSearch, double gpaToSearch)
{
	if (m_List.empty())
		throw E_NullList();

	size_t sizeBefore = m_NumOfElements;
	// remove by name
	if (matchName)
	{
		m_List.remove_if([&](Student temp)
		{
			return nameToSearch == temp.Student::getName();
		});
	}
	// remove by grade level
	else if (matchLevel)
	{
		m_List.remove_if([&](Student temp)
		{
			return levelToSearch == temp.Student::getLevel();
		});
	}
	// remove by gpa
	else if (matchGpa)
	{
		m_List.remove_if([&](Student temp)
		{
			return gpaToSearch > temp.Student::getGPA();
		});
	}

	// return the number of elements deleted
	m_NumOfElements = std::distance(m_List.begin(), m_List.end());
	return sizeBefore - m_NumOfElements;
}

void SinglyLinkedList::erase_after(size_t m_Index)
{
	if (m_List.empty())
		throw E_NullList();
	// check if the index is valid and contains an element after it
	if (m_Index >= m_NumOfElements - 1)
		throw E_IndexOutOfBounds(m_Index, m_NumOfElements - 1);

	// advance the iterator to the index
	auto it = m_List.begin();
	advance(it, m_Index);

	// erase the element after the iterator
	m_List.erase_after(it);
	m_NumOfElements--;
}

void SinglyLinkedList::update_element(size_t m_Index, Student m_newData)
{
	if (m_List.empty())
		throw E_NullList();
	if (m_Index >= m_NumOfElements)
		throw E_IndexOutOfBounds(m_Index, m_NumOfElements - 1);

	// advance the iterator to the index
	auto it = m_List.begin();
	advance(it, m_Index);

	// update the student at the iterator at the index
	*it = m_newData;
}

Student SinglyLinkedList::front() const
{
	if (m_List.empty())
		throw E_NullList();

	return m_List.front();
}

std::forward_list<Student>::const_iterator SinglyLinkedList::begin() const
{
	return m_List.cbegin();
}

Student SinglyLinkedList::back() const
{
	if (m_List.empty())
		throw E_NullList();

	// advance the iterator to the last element
	auto it = m_List.begin();
	advance(it, m_NumOfElements - 1);

	// return the element at the iterator
	return *it;
}

std::forward_list<Student>::const_iterator SinglyLinkedList::end() const
{
	return m_List.cend();
}

void SinglyLinkedList::sort()
{
	m_List.sort();
}

void SinglyLinkedList::reverse()
{
	m_List.reverse();
}

void SinglyLinkedList::resize(size_t m_newSize)
{
	m_List.resize(m_newSize, Student());
	m_NumOfElements = m_newSize;
}

void SinglyLinkedList::clear()
{
	m_List.clear();
	m_NumOfElements = 0;
}

void SinglyLinkedList::push_from_file(std::string m_FileName)
{
	std::fstream file;
	file.open(m_FileName, std::ios::in);

	// advance the iterator the the last node
	auto it = m_List.before_begin();
	if (!m_List.empty())
		advance(it, m_NumOfElements - 1);

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
		m_NumOfElements++;
	}
	file.close();
}

std::ostream &operator <<(std::ostream &out, const SinglyLinkedList &obj)
{
	if (obj.m_List.empty())
	{
		out << "\n\t\t\tEmpty list.";
	}
	else
	{
		// iterate through the list using begin() and end()
		for (auto it = obj.begin(); it != obj.end(); it++)
		{
			out << "\n\t\t\t" << &(*it) << " (" << *it << ")";
		}

	}
	return out;
}



// Exception Errors
SinglyLinkedList::E_IndexOutOfBounds::E_IndexOutOfBounds(size_t p_Index, size_t p_UpperBound)
	: m_Index(p_Index),
	m_UpperBound(p_UpperBound)
{
}

std::string SinglyLinkedList::E_IndexOutOfBounds::GetExceptionName() const
{
	return "Index Out Of Bounds";
}

std::string SinglyLinkedList::E_IndexOutOfBounds::GetExceptionMessage() const
{
	std::stringstream ss;
	ss << "Index (" << m_Index << ") is out of Bounds (0..." << m_UpperBound << ")";
	return ss.str();
}

SinglyLinkedList::E_NullList::E_NullList()
{}

std::string SinglyLinkedList::E_NullList::GetExceptionName() const
{
	return "Null List";
}

std::string SinglyLinkedList::E_NullList::GetExceptionMessage() const
{
	return "The List is Empty!";
}