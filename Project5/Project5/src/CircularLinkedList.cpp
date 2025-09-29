#include "CircularLinkedList.h"
#include "ExceptionInterface.h"
#include <iterator>
#include <sstream>

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

	m_TailPtr->GetNext() = m_HeadPtr;
	m_NumOfElements++;
}

size_t CircularLinkedList::GetSize() const
{
	return m_NumOfElements;
}

void CircularLinkedList::Insert(size_t p_Index) const
{
}

void CircularLinkedList::DeleteAt(size_t p_Index) const
{
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
}

bool CircularLinkedList::ReadFile(const char* p_FileName)
{
	return false;
}

void CircularLinkedList::PushFront(const value_type& p_NewElement)
{
	if (!m_HeadPtr)
	{
		m_HeadPtr = new Node();
		m_HeadPtr->GetData() = p_NewElement;
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
	if (!m_TailPtr)
		throw E_NullList();
}

CircularLinkedList::value_type& CircularLinkedList::Front()
{
	return (*this)[m_NumOfElements - 1];
}

void CircularLinkedList::PopBack()
{
	if (!m_TailPtr)
		throw E_NullList();
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
	if (!m_CurrentNode->GetNext())
	{
		*this = m_CircularLinkedList.rend();
		return *this;
	}

	m_CurrentNode = m_CurrentNode->GetNext();
	m_Increment++;

	return *this;
}

CircularLinkedList::ListReverseIter CircularLinkedList::ListReverseIter::operator++(int)
{
	auto temp = *this;

	if (!m_CurrentNode->HasNext())
	{
		*this = m_CircularLinkedList.rend();
		return *this;
	}

	m_CurrentNode = m_CurrentNode->GetNext();
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
