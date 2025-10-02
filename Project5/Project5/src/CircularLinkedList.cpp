#include "CircularLinkedList.h"
#include "ExceptionInterface.h"
#include <iterator>
#include <sstream>
#include <fstream>
#include "Input.h"


CircularLinkedList::ListIter::ListIter(CircularLinkedList& p_CircularLinkedList, Node* p_CurrentNode, size_t p_Increment)
	: m_CircularLinkedList(p_CircularLinkedList),
	m_CurrentNode(p_CurrentNode),
	m_Increment(p_Increment)
{}

CircularLinkedList::iterator& CircularLinkedList::ListIter::operator++()
{
	if (!m_CurrentNode->GetNext())
	{
		*this = m_CircularLinkedList.end();
		return *this;
	}

	m_CurrentNode = m_CurrentNode->GetNext();
	m_Increment++;

	return *this;
}

CircularLinkedList::iterator CircularLinkedList::ListIter::operator++(int)
{
	auto temp = *this;

	if (!m_CurrentNode->HasNext())
	{
		*this = m_CircularLinkedList.end();
		return *this;
	}

	m_CurrentNode = m_CurrentNode->GetNext();
	m_Increment++;

	return temp;
}

bool CircularLinkedList::ListIter::operator!=(const ListIter& p_Other) const
{
	return this->m_Increment != p_Other.m_Increment;
}

CircularLinkedList::value_type& CircularLinkedList::ListIter::operator*()
{
	return m_CurrentNode->GetData();
}

CircularLinkedList::ListIter& CircularLinkedList::ListIter::operator=(const ListIter& p_Other)
{
	this->m_Increment = p_Other.m_Increment;
	this->m_CircularLinkedList = p_Other.m_CircularLinkedList;
	this->m_CurrentNode = p_Other.m_CurrentNode;

	return *this;
}

void CircularLinkedList::PushBack(const value_type& p_NewElement)
{
	if (!m_TailPtr)
	{
		m_HeadPtr = new Node();
		m_HeadPtr->GetData() = p_NewElement;
		m_TailPtr = m_HeadPtr;
		m_NumOfElements++;
		return;
	}

	Node* oldTail = m_TailPtr;

	m_TailPtr = new Node();
	m_TailPtr->GetData() = p_NewElement;

	oldTail->GetNext() = m_TailPtr;
	m_TailPtr->GetPrevious() = oldTail;

	m_TailPtr->GetNext() = m_HeadPtr;
	m_HeadPtr->GetPrevious() = m_TailPtr;

	m_NumOfElements++;
}

size_t CircularLinkedList::GetSize() const
{
	return m_NumOfElements;
}

void CircularLinkedList::Insert(value_type p_NewElement, size_t p_Index)
{
	if (p_Index >= m_NumOfElements)
		throw E_IndexOutOfBounds(p_Index, m_NumOfElements);

	if (p_Index == 0)
	{
		PushFront(p_NewElement);
		return;
	}

	if (p_Index == m_NumOfElements - 1)
	{
		PushBack(p_NewElement);
		return;
	}

	size_t increment = p_Index - 1;
	Node* ptr = m_HeadPtr;
	Node* cachedNextPtr = nullptr;

	while (increment > 0 && ptr->HasNext())
	{
		increment--;
		ptr = ptr->GetNext();
	}

	cachedNextPtr = ptr->GetNext();

	ptr->GetNext() = new Node();
	ptr->GetNext()->GetData() = p_NewElement;

	ptr->GetNext()->GetNext() = cachedNextPtr;
	ptr->GetNext()->GetPrevious() = ptr;
	
	cachedNextPtr->GetPrevious() = ptr->GetNext();

	m_NumOfElements++;
}

void CircularLinkedList::DeleteAt(size_t p_Index)
{
	if (m_NumOfElements == 0)
		throw E_NullList();

	if (p_Index >= m_NumOfElements)
		throw E_IndexOutOfBounds(p_Index, m_NumOfElements);

	if (p_Index == 0)
	{
		PopFront();
		return;
	}

	if (p_Index == m_NumOfElements - 1)
	{
		PopBack();
		return;
	}


	size_t increment = p_Index - 1;
	Node* ptr = m_HeadPtr;
	Node* cachedNextPtr = nullptr;

	while (increment > 0 && ptr->HasNext())
	{
		increment--;
		ptr = ptr->GetNext();
	}

	if (!ptr->GetNext()->HasNext())
	{
		delete ptr->GetNext();
		return;
	}

	cachedNextPtr = ptr->GetNext()->GetNext();
	delete ptr->GetNext();

	ptr->GetNext() = cachedNextPtr;
	cachedNextPtr->GetPrevious() = ptr;

	m_NumOfElements--;
}

void CircularLinkedList::DeleteAt(iterator p_Iter)
{
	DeleteAt(p_Iter.GetIncrement());
}

void CircularLinkedList::DeleteRange(iterator p_Begin, iterator p_End)
{
	size_t rangeSize = p_End.GetIncrement() - p_Begin.GetIncrement();
	for (size_t i = 0; i < rangeSize; i++)
		this->DeleteAt(p_Begin.GetIncrement());
}

void CircularLinkedList::Swap(CircularLinkedList& p_Other)
{
	auto tempHead = this->m_HeadPtr;
	auto tempTail = this->m_TailPtr;
	auto tempSize = this->m_NumOfElements;
	this->m_HeadPtr = p_Other.m_HeadPtr;
	this->m_TailPtr = p_Other.m_TailPtr;
	this->m_NumOfElements = p_Other.m_NumOfElements;
	p_Other.m_HeadPtr = tempHead;
	p_Other.m_TailPtr = tempTail;
	p_Other.m_NumOfElements = tempSize;
}

CircularLinkedList::iterator CircularLinkedList::begin()
{
	if (!m_HeadPtr)
		return iterator(*this, nullptr, NULL);

	return iterator(*this, m_HeadPtr, 0);
}

CircularLinkedList::iterator CircularLinkedList::end()
{
	if (!m_TailPtr)
		return iterator(*this, nullptr, NULL);

	return iterator(*this, m_TailPtr, GetSize());
}

CircularLinkedList::reverse_iterator CircularLinkedList::rbegin()
{
	if (!m_TailPtr)
		return reverse_iterator(*this, nullptr, NULL);

	return reverse_iterator(*this, m_TailPtr, 0);
}

CircularLinkedList::reverse_iterator CircularLinkedList::rend()
{
	if (!m_TailPtr)
		return reverse_iterator(*this, nullptr, NULL);

	return reverse_iterator(*this, m_HeadPtr, GetSize());
}

CircularLinkedList::value_type& CircularLinkedList::Node::GetData()
{
	return m_Data;
}

CircularLinkedList::Node*& CircularLinkedList::Node::GetNext()
{
	return m_Next;
}

bool CircularLinkedList::Node::HasNext() const
{
	return m_Next != nullptr;
}

CircularLinkedList::Node*& CircularLinkedList::Node::GetPrevious()
{
	return m_Prev;
}

bool CircularLinkedList::Node::HasPrevious() const
{
	return m_Prev != nullptr;
}

CircularLinkedList::~CircularLinkedList()
{
	Clear();
}

void CircularLinkedList::Clear()
{
	Node* ptr = m_HeadPtr;

	if (!ptr)
		return;

	for (size_t i = 0; i < m_NumOfElements; i++)
	{
		Node* temp = ptr;
		ptr = ptr->GetNext();
		delete temp;
	}

	m_HeadPtr = nullptr;
	m_TailPtr = nullptr;
	m_NumOfElements = 0;
}

void CircularLinkedList::Resize(size_t p_NewSize)
{

	size_t numOfElements = m_NumOfElements;

	if (numOfElements == p_NewSize)
		return;

	if (numOfElements > p_NewSize)
	{
		for(size_t i = 0; i < numOfElements - p_NewSize; i++)
			PopBack();
	}
	else
	{
		for (size_t i = 0; i < p_NewSize - numOfElements; i++)
			PushBack(value_type());
	}

	m_NumOfElements = p_NewSize;
}

bool CircularLinkedList::PushFileBack(const char* p_FileName)
{
	// get the file name
	std::string fileName = p_FileName;
	std::fstream file;

	// open the file to read
	file.open(fileName, std::ios::in);

	// check if successful open
	if (!file)
	{
		std::cout << "\n\tERROR: Could not open file.";
		return false;
	}

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
		this->PushBack(temp);
	}

	return true;
}

bool CircularLinkedList::PushFileFront(const char* p_FileName)
{
	// get the file name
	std::string fileName = p_FileName;
	std::fstream file;

	// open the file to read
	file.open(fileName, std::ios::in);

	// check if successful open
	if (!file)
	{
		std::cout << "\n\tERROR: Could not open file.";
		return false;
	}

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
		this->PushFront(temp);
	}

	return true;
}

void CircularLinkedList::PushFront(const value_type& p_NewElement)
{
	if (!m_HeadPtr)
	{
		m_HeadPtr = new Node();
		m_HeadPtr->GetData() = p_NewElement;
		m_TailPtr = m_HeadPtr;
		m_NumOfElements++;
		return;
	}
	
	Node* oldHead = m_HeadPtr;

	m_HeadPtr = new Node();
	m_HeadPtr->GetData() = p_NewElement;

	m_HeadPtr->GetNext() = oldHead;
	oldHead->GetPrevious() = m_HeadPtr;

	m_TailPtr->GetNext() = m_HeadPtr;
	m_HeadPtr->GetPrevious() = m_TailPtr;

	m_NumOfElements++;
}

void CircularLinkedList::PopFront()
{
	if (!m_HeadPtr)
		throw E_NullList();

	if (!m_HeadPtr->HasNext())
	{
		m_NumOfElements--;
		delete m_HeadPtr;
	}

	Node* cachedNextNode = m_HeadPtr->GetNext();
	delete m_HeadPtr;
	m_HeadPtr = cachedNextNode;

	m_HeadPtr->GetPrevious() = m_TailPtr;
	m_TailPtr->GetNext() = m_HeadPtr;

	m_NumOfElements--;
}

CircularLinkedList::value_type& CircularLinkedList::Front()
{
	if (m_NumOfElements == 0)
		throw E_NullList();

	return m_HeadPtr->GetData();
}

CircularLinkedList::value_type& CircularLinkedList::Back()
{
	if (m_NumOfElements == 0)
		throw E_NullList();

	return m_TailPtr->GetData();
}

void CircularLinkedList::PopBack()
{
	if (!m_TailPtr)
		throw E_NullList();

	if (!m_TailPtr->HasPrevious())
	{
		m_NumOfElements--;
		delete m_TailPtr;
	}

	Node* cachedNextNode = m_TailPtr->GetPrevious();
	delete m_TailPtr;
	m_TailPtr = cachedNextNode;

	m_HeadPtr->GetPrevious() = m_TailPtr;
	m_TailPtr->GetNext() = m_HeadPtr;

	m_NumOfElements--;
}

CircularLinkedList::value_type& CircularLinkedList::operator [](size_t p_Index)
{
	Node* ptr = m_HeadPtr;

	if (!ptr)
		throw E_NullList();

	if (p_Index >= m_NumOfElements)
		throw E_IndexOutOfBounds(p_Index, m_NumOfElements - 1);

	size_t increment = p_Index;
		
	for (size_t i = 0; i <= p_Index; i++)
		ptr = ptr->GetNext();

	return ptr->GetData();
}

void CircularLinkedList::Sort()
{
	auto head = m_HeadPtr;

	if (!head || head->GetNext() == head) 
		return; // empty or 1 node

	Node* i = head;
	do 
	{
		Node* minNode = i;
		Node* j = i->GetNext();

		while (j != head) 
		{
			if (j->GetData() < minNode->GetData()) 
				minNode = j;

			j = j->GetNext();
		}

		// Swap data
		if (minNode != i) 
		{
			value_type temp = i->GetData();
			i->GetData() = minNode->GetData();
			minNode->GetData() = temp;
		}

		i = i->GetNext();
	} while (i != head);
}

CircularLinkedList::E_IndexOutOfBounds::E_IndexOutOfBounds(size_t p_Index, size_t p_UpperBound)
	: m_Index(p_Index),
	m_UpperBound(p_UpperBound)
{}

std::string CircularLinkedList::E_IndexOutOfBounds::GetExceptionName() const
{
	return "Index Out Of Bounds";
}

std::string CircularLinkedList::E_IndexOutOfBounds::GetExceptionMessage() const
{
	std::stringstream ss;
	ss << "Index (" << m_Index << ") is out of Bounds (0..." << m_UpperBound << ")";
	return std::string();
}

CircularLinkedList::E_NullList::E_NullList()
{}

std::string CircularLinkedList::E_NullList::GetExceptionName() const
{
	return "Null List";
}

std::string CircularLinkedList::E_NullList::GetExceptionMessage() const
{
	return "The List is Empty!";
}

CircularLinkedList::ListReverseIter::ListReverseIter(CircularLinkedList& p_CircularLinkedList, Node* p_CurrentNode, size_t p_Increment)
	: m_CircularLinkedList(p_CircularLinkedList),
	m_CurrentNode(p_CurrentNode),
	m_Increment(p_Increment)
{}

CircularLinkedList::ListReverseIter& CircularLinkedList::ListReverseIter::operator++()
{
	if (!m_CurrentNode->HasPrevious())
	{
		*this = m_CircularLinkedList.rend();
		return *this;
	}

	m_CurrentNode = m_CurrentNode->GetPrevious();
	m_Increment++;

	return *this;
}

CircularLinkedList::ListReverseIter CircularLinkedList::ListReverseIter::operator++(int)
{
	auto temp = *this;

	if (!m_CurrentNode->HasPrevious())
	{
		*this = m_CircularLinkedList.rend();
		return *this;
	}

	m_CurrentNode = m_CurrentNode->GetPrevious();
	m_Increment++;

	return temp;
}

bool CircularLinkedList::ListReverseIter::operator!=(const ListReverseIter& p_Other) const
{
	return this->m_Increment != p_Other.m_Increment;
}

CircularLinkedList::value_type& CircularLinkedList::ListReverseIter::operator*()
{
	return m_CurrentNode->GetData();
}

CircularLinkedList::ListReverseIter& CircularLinkedList::ListReverseIter::operator=(const ListReverseIter& p_Other)
{
	this->m_Increment = p_Other.m_Increment;
	this->m_CircularLinkedList = p_Other.m_CircularLinkedList;
	this->m_CurrentNode = p_Other.m_CurrentNode;

	return *this;
}

size_t CircularLinkedList::ListReverseIter::GetIncrement() const
{
	return m_Increment;
}


size_t CircularLinkedList::ListIter::GetIncrement() const
{
	return m_Increment;
}

const CircularLinkedList::Node* CircularLinkedList::ListReverseIter::GetPtr() const
{
	return m_CurrentNode;
}
