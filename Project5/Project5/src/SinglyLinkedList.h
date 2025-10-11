#pragma once
#include "Student.h"
#include "ExceptionInterface.h"
#include <iostream>
#include <forward_list>

class SinglyLinkedList
{
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

public:
	/*
	* PreCondition: N/A
	* PostCondition: Initialize private members with default values
	*/
	SinglyLinkedList();

	/*
	* PreCondition: N/A
	* PostCondition: Return true if the list is empty, else return false
	*/
	bool empty() const;

	/*
	* PreCondition: N/A
	* PostCondition: Return the number of elements currently in the list
	*/
	int getNumOfElements() const;

	/*
	* PreCondition: Student data to push is passed
	* PostCondition: Push the element to the front of the list
	*/
	void push_front(Student m_Data);

	/*
	* PreCondition: Student data to push is passed
	* PostCondition: Push the element at the end of the list
	*/
	void push_back(Student m_Data);

	/*
	* PreCondition: Valid index and student data to be inserted are passed
	* PostCondition: Insert the element after the given index
	*/
	void insert_after(size_t m_Index, Student m_Data);

	/*
	* PreCondition: List must not be empty
	* PostCondition: Pop the element at the front
	*/
	void pop_front();

	/*
	* PreCondition: List must not be empty
	* PostCondition: Pop the element at the back
	*/
	void pop_back();

	/*
	* PreCondition: List must not be empty. Student to be removed is passed
	* PostCondition: remove any elements in the list that match the student to be removed
	*/
	int remove(Student m_Data);

	/*
	* PreCondition: List mut not be empty. Boolean statements regarding the criterion of the student to remove are passed.
	* The respective argument is also passed to determine which students are removed
	* PostCondition: Remove students based on the criteria and the argument passed
	*/
	int remove_if(bool matchName = false, bool matchLevel = false, bool matchGpa = false, 
		std::string nameToSearch = "", std::string levelToSearch = "", double gpaToSearch = 0);

	/*
	* PreCondition: List must not be empty. The Index must be valid and has to have an element after it.
	* PostCondition: Remove the element after the given index
	*/
	void erase_after(size_t m_Index);

	/*
	* PreCondition: List must not be empty. Valid index and new student data are passed
	* PostCondition: Reinitialize the element at the index with the new student data
	*/
	void update_element(size_t m_Index, Student m_newData);

	/*
	* PreCondition: List must not be empty
	* PostCondition: Return the element at the front of the list
	*/
	Student front() const;

	/*
	* PreCondition: List must not be empty
	* PostCondition: Return an iterator referring to the first element
	*/
	std::forward_list<Student>::iterator begin();

	/*
	* PreCondition: List must not be empty
	* PostCondition: Return the element at the back of the list
	*/
	Student back() const;

	/*
	* PreCondition: List must not be empty
	* PostCondition: Return an iterator referring to past-the-end element
	*/
	std::forward_list<Student>::iterator end();

	/*
	* PreCondition: N/A
	* PostCondition: Sorts the list in alphabetical order
	*/
	void sort();

	/*
	* PreCondition: N/A
	* PostCondition: Reverses the order of the elements
	*/
	void reverse();

	/*
	* PreCondition: Size must be a positive integer
	* PostCondition: Resize the list to the given size
	*/
	void resize(size_t m_Size);

	/*
	* PreCondition: N/A
	* PostCondition: Clear the list of elements
	*/
	void clear();

	/*
	* PreCondition: FileName must be the name of a file that can successfully be opened
	* PostCondition: Read the file and push the contents of the file into the list
	*/
	void push_from_file(std::string m_FileName);

	friend std::ostream &operator <<(std::ostream &out, SinglyLinkedList &obj);

private:
	std::forward_list<Student> m_List;
	size_t m_NumOfElements;
};

