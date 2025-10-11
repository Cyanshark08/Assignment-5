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
	SinglyLinkedList();
	bool empty() const;
	int getNumOfElements() const;
	void push_front(Student m_Data);
	void push_back(Student m_Data);
	void insert_after(size_t m_Index, Student m_Data);
	void pop_front();
	void pop_back();
	int remove(Student m_Data);
	int remove_if(bool matchName = false, bool matchLevel = false, bool matchGpa = false, 
		std::string nameToSearch = "", std::string levelToSearch = "", double gpaToSearch = 0);
	void erase_after(size_t m_Index);
	void update_element(size_t m_Index, Student m_newData);
	Student front() const;
	std::forward_list<Student>::const_iterator begin() const;
	Student back() const;
	std::forward_list<Student>::const_iterator end() const;
	void sort();
	void reverse();
	void resize(size_t m_Size);
	void clear();
	void push_from_file(std::string m_FileName);

	friend std::ostream &operator <<(std::ostream &out, const SinglyLinkedList &obj);


private:
	std::forward_list<Student> m_List;
	size_t m_NumOfElements;
};

