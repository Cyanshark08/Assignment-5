#pragma once

#include "SinglyNode.h"
#include "ExceptionInterface.h"

template <class t_Type>
class SinglyList
{
public:

	SinglyList()
	{
		head = nullptr;
	}

	~SinglyList()
	{
		// pointer to current node
		SinglyNode <t_Type> *nodePtr = head;
		
		// traverse through the list
		while (nodePtr != nullptr)
		{
			// pointer to the next node
			SinglyNode <t_Type> *nextNode = nodePtr->next;

			// delete the current node
			delete nodePtr;

			// reinitialize nodePtr
			nodePtr = nextNode;
		}
	}

	SinglyList clear()
	{
		// pointer to current node
		SinglyNode <t_Type> *nodePtr = head;

		// traverse through the list
		while (nodePtr != nullptr)
		{
			// pointer to the next node
			SinglyNode <t_Type> *nextNode = nodePtr->next;

			// delete the current node
			delete nodePtr;

			// reinitialize nodePtr
			nodePtr = nextNode;
		}
	}

	bool empty() const
	{
		return !head;
	}

private:
	SinglyNode<t_Type> *head;
};



