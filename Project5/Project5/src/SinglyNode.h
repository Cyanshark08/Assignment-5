#pragma once

#include <iostream>

template <class t_Type>
class SinglyNode
{
public:
	SinglyNode(t_Type newValue)
	{
		data = newValue;
		next = nullptr;
	}

	friend std::ostream &operator<<(std::ostream &out, const SinglyNode &obj)
	{
		out << obj.data;
		return out;
	}

public:
	t_Type data;
	SinglyNode<t_Type> *next;
};

