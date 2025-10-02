#pragma once
#include <iterator>
#include "ExceptionInterface.h"
#include "Student.h"

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
typedef Student t_Type;
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

	/*
	* Forward Iterator for Circular Linked List
	*/
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

		size_t GetIncrement() const;

		const Node* GetPtr() const;

	private:
		Node* m_CurrentNode{ nullptr };
		CircularLinkedList& m_CircularLinkedList;
		size_t m_Increment;
	};

	typedef ListIter iterator;

	/*
	* Reverse Iterator for Circular Linked List
	*/
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

		size_t GetIncrement() const;

		const Node* GetPtr() const;

	private:
		Node* m_CurrentNode{ nullptr };
		CircularLinkedList& m_CircularLinkedList;
		size_t m_Increment;
	};

	typedef ListReverseIter reverse_iterator;

public:
	CircularLinkedList() = default;

	~CircularLinkedList();

	/*
	* Precondition: none
	* Postcondition: clears list
	*/
	void Clear();

	/*
	* Precondition: give size
	* Postcondition: restructures list to given size
	*/
	void Resize(size_t p_NewSize);

	/*
	* Precondition: pass file name
	* Postcondition: pushes back all file elements
	*/
	bool PushFileBack(const char* p_FileName);

	/*
	* Precondition: pass file name
	* Postcondition: pushes front all file elements
	*/
	bool PushFileFront(const char* p_FileName);

	/*
	* Precondition: Pass element
	* Postcondition: pushes element to the front
	*/
	void PushFront(const value_type& p_NewElement);

	/*
	* Precondition: List must have an element
	* Postcondition: pops the front element
	*/
	void PopFront();

	/*
	* Precondition: List must have an element
	* Postcondition: pops the front element
	*/
	value_type& Front();

	/*
	* Precondition: List must have an element
	* Postcondition: pops the front element
	*/
	value_type& Back();

	/*
	* Precondition: List must have an element
	* Postcondition: pops the back element
	*/
	void PopBack();

	/*
	* Precondition: pass element
	* Postcondition: pushes element to the back
	*/
	void PushBack(const value_type& p_NewElement);

	/*
	* Precondition: none
	* Postcondition: returns size of list
	*/
	size_t GetSize() const;
	
	/*
	* Precondition: pass element and index
	* Postcondition: inserts element at index
	*/
	void Insert(value_type p_NewElement,  size_t p_Index);

	/*
	* Precondition: List must have an element
	* Postcondition: Deletes element at index
	*/
	void DeleteAt(size_t p_Index);

	/*
	* Precondition: List must have an element
	* Postcondition: deletes element at iterator
	*/
	void DeleteAt(iterator p_Iter);

	/*
	* Precondition: List must have an element
	* Postcondition: deletes elements to and from iterators
	*/
	void DeleteRange(iterator p_Begin, iterator p_End);

	void Swap(CircularLinkedList& p_Other);

	iterator begin();

	iterator end();

	reverse_iterator rbegin();

	reverse_iterator rend();

	value_type& operator [](size_t p_Index);

	void Sort();

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


typedef CircularLinkedList circular_list;