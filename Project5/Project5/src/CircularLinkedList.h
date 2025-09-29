#pragma once
#include <iterator>
#include "ExceptionInterface.h"

/*
* 
* This class is a doubly-circularly-linked list that
* links forward, backward, and loops back around.
* 
* It implements both 
* 
*/

/*
* TODO:
*  - Finish Class Implementation
* 
* NOTE: After I finish implementing the class,
* I will turn it into a template class
* (templates are harder to debug)
* 
*/
typedef int t_Type;
class CircularLinkedList
{
public:
	typedef std::ptrdiff_t difference_type;
	typedef size_t size_type;
	typedef t_Type value_type;
	typedef t_Type* pointer;
	typedef t_Type& reference;

	class Node
	{
	public:
		value_type& GetData();
		Node*& GetNext();
		bool HasNext() const;

		Node*& GetPrevious();
		bool HasPrevious() const;

	private:
		value_type m_Data;
		Node* m_Next = nullptr;
		Node* m_Prev = nullptr;
	};

	class ListIter
	{
	public:
		ListIter(CircularLinkedList& p_CircularLinkedList, Node* p_CurrentNode, size_t p_Increment);

		ListIter& operator++();
		ListIter operator++(int);

		//ContainerIterator& operator--();
		//ContainerIterator operator--(int);

		bool operator!=(const ListIter& p_Other) const;

		value_type& operator*();

		ListIter& operator=(const ListIter& p_Other);

	private:
		Node* m_CurrentNode{ nullptr };
		CircularLinkedList& m_CircularLinkedList;
		size_t m_Increment;
	};

	typedef ListIter iterator;

	class ListReverseIter
	{
	public:
		ListReverseIter(CircularLinkedList& p_CircularLinkedList, Node* p_CurrentNode, size_t p_Increment);

		ListReverseIter& operator++();
		ListReverseIter operator++(int);

		//ContainerIterator& operator--();
		//ContainerIterator operator--(int);

		bool operator!=(const ListReverseIter& p_Other) const;

		value_type& operator*();

		ListReverseIter& operator=(const ListReverseIter& p_Other);

	private:
		Node* m_CurrentNode{ nullptr };
		CircularLinkedList& m_CircularLinkedList;
		size_t m_Increment;
	};

	typedef ListReverseIter reverse_iterator;

public:
	CircularLinkedList() = default;

	~CircularLinkedList();

	void Clear();

	void Resize(size_t p_NewSize);

	bool ReadFile(const char* p_FileName);

	void PushFront(const value_type& p_NewElement);

	void PopFront();

	value_type& Front();

	void PopBack();

	void PushBack(const value_type& p_NewElement);

	size_t GetSize() const;
	
	void Insert(size_t p_Index) const;

	void DeleteAt(size_t p_Index) const;

	iterator begin();

	iterator end();

	reverse_iterator rbegin();

	reverse_iterator rend();

	value_type& operator [](size_t p_Index);

public:

	class E_IndexOutOfBounds : public ExceptionInterface
	{
	public:
		E_IndexOutOfBounds(size_t p_Index, size_t p_UpperBound);

	private:
		std::string GetExceptionName() const override;
		std::string GetExceptionMessage() const override;

	private:
		size_t m_Index;
		size_t m_UpperBound;
	};

	class E_NullList : public ExceptionInterface
	{
	public:
		E_NullList();

	private:
		std::string GetExceptionName() const override;
		std::string GetExceptionMessage() const override;
	};

private:
	Node* m_HeadPtr{ nullptr };
	Node* m_TailPtr{ nullptr };
	size_t m_NumOfElements{ 0 };

};